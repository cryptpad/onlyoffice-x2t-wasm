FROM ubuntu:22.04 AS base
SHELL ["/bin/bash", "-c"]

RUN --mount=target=/var/lib/apt/lists,type=cache,sharing=locked \
    --mount=target=/var/cache/apt,type=cache,sharing=locked \
    apt update \
    && apt install -y \
       git \
       python-is-python3 \
       xz-utils \
       lbzip2 \
       automake \
       libtool \
       autoconf \
       make \
       qt6-base-dev \
       build-essential \
       cmake \
       zip \
       pkg-config

WORKDIR /
RUN git clone https://github.com/emscripten-core/emsdk.git
WORKDIR /emsdk
ARG emversion=4.0.2
RUN git fetch -a \
 && git checkout $emversion
RUN ./emsdk install $emversion
RUN ./emsdk activate $emversion

RUN . /emsdk/emsdk_env.sh && qtchooser -install qt6 $(which qmake6)
ENV QT_SELECT=qt6
WORKDIR /
COPY embuild.sh /bin/embuild.sh


FROM base AS freetype #  TODO remove?
COPY core/DesktopEditor/freetype-2.10.4 /freetype
WORKDIR /freetype
# TODO do I need this somwhere below?
# Do not include zlib in the build, but link it later
#RUN sed -i -e 's,$$OFFICEUTILS_PATH/src/zlib[^ ]*\.c,,' \
#    DesktopEditor/graphics/pro/freetype.pri
RUN bash ./autogen.sh
RUN . /emsdk/emsdk_env.sh \
 && emconfigure ./configure
RUN . /emsdk/emsdk_env.sh \
 && emmake make
RUN . /emsdk/emsdk_env.sh \
 && emmake make install


FROM base AS build-tools
RUN git clone https://github.com/ONLYOFFICE/build_tools.git
WORKDIR /build_tools
# TODO RUN git checkout pin some version


FROM base AS harfbuzz
COPY core/Common/3dParty/harfbuzz /core/Common/3dParty/harfbuzz
COPY --from=build-tools /build_tools/scripts/base.py /core/Common/3dParty/harfbuzz/base.py
COPY --from=build-tools /build_tools/scripts/config.py /core/Common/3dParty/harfbuzz/config.py
WORKDIR /core/Common/3dParty/harfbuzz
RUN python make.py



FROM base as hyphen
COPY core/Common/3dParty/hyphen /core/Common/3dParty/hyphen
COPY --from=build-tools /build_tools /build_tools
WORKDIR /build_tools/scripts/core_common/modules
RUN python -c "import hyphen; hyphen.make()"
WORKDIR /core/Common/3dParty/hyphen/hyphen
RUN autoreconf -fvi
RUN . /emsdk/emsdk_env.sh \
 && emconfigure ./configure
RUN . /emsdk/emsdk_env.sh \
 && emmake make
RUN . /emsdk/emsdk_env.sh \
 && emmake make install
# outputs
# - /usr/local/lib/libhyphen.a
# - /usr/local/include/hyphen.h
# - /core/Common/3dParty/hyphen/hyphen/hnjalloc.h


# TODO remove?
# FROM base AS hunspell
# COPY core/Common/3dParty/hunspell /core/Common/3dParty/hunspell
# COPY --from=build-tools /build_tools/scripts/base.py /core/Common/3dParty/hunspell/base.py
# COPY --from=build-tools /build_tools/scripts/config.py /core/Common/3dParty/hunspell/config.py
# WORKDIR /core/Common/3dParty/hunspell
# RUN python before.py
# RUN find . -name "*.h"
# RUN exit 1


FROM base AS gumbo
RUN git clone https://github.com/google/gumbo-parser.git
WORKDIR /gumbo-parser
RUN git checkout aa91b2
RUN ./autogen.sh
RUN . /emsdk/emsdk_env.sh \
 && emconfigure ./configure
RUN . /emsdk/emsdk_env.sh \
 && emmake make
RUN . /emsdk/emsdk_env.sh \
 && emmake make install



FROM base AS katana
WORKDIR /
RUN git clone https://github.com/jasenhuang/katana-parser.git
WORKDIR /katana-parser
RUN git checkout be6df4
RUN ./autogen.sh
RUN . /emsdk/emsdk_env.sh \
 && emconfigure ./configure
RUN . /emsdk/emsdk_env.sh \
 && emmake make
RUN . /emsdk/emsdk_env.sh \
 && emmake make install



FROM base AS boost
# emscriptens boost does not work because of missing symbols
WORKDIR /
RUN git clone https://github.com/boostorg/boost.git
WORKDIR /boost
RUN git checkout boost-1.84.0
RUN git submodule update --init --recursive
RUN . /emsdk/emsdk_env.sh \
 && CXXFLAGS=-fms-extensions emcmake cmake '-DBOOST_EXCLUDE_LIBRARIES=context;cobalt;coroutine;fiber;log;thread;wave;type_erasure;serialization;locale;contract;graph'
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
 . /emsdk/emsdk_env.sh \
 && emmake make
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
 . /emsdk/emsdk_env.sh \
 && emmake make install
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    cp -r /emsdk/upstream/emscripten/cache/sysroot/include/boost /usr/local/include/
# Outputs /usr/local/include/boost



FROM base AS UnicodeConverter
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/DesktopEditor/common /core/DesktopEditor/common
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh UnicodeConverter
RUN mkdir -p /core/build/lib/linux_64
RUN mv /core/UnicodeConverter.o /core/build/lib/linux_64/libUnicodeConverter.a



FROM base AS Common
COPY core/Common /core/Common
COPY core/DesktopEditor/common /core/DesktopEditor/common
COPY core/DesktopEditor/graphics /core/DesktopEditor/graphics
COPY core/DesktopEditor/xml /core/DesktopEditor/xml
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/OfficeUtils /core/OfficeUtils
COPY --from=UnicodeConverter /core/build/lib/linux_64/ /core/build/lib/linux_64/
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh Common
# outputs ./build/lib/linux_64/libkernel.so



FROM base as graphics
COPY core/Common /core/Common
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/OfficeUtils/ /core/OfficeUtils/
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/Common/3dParty/harfbuzz /core/Common/3dParty/harfbuzz
COPY --from=harfbuzz /core/Common/3dParty/harfbuzz/ /core/Common/3dParty/harfbuzz/
COPY --from=Common /core/build/lib/linux_64/ /core/build/lib/linux_64/
COPY --from=katana /katana-parser /katana-parser
COPY --from=hyphen /core/Common/3dParty/hyphen/hyphen /core/Common/3dParty/hyphen/hyphen
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh -c "-Wno-register" DesktopEditor/graphics/pro
# Outputs build/lib/linux_64/libkernel.so


FROM base AS txtfile
COPY core/Common /core/Common
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/TxtFile /core/TxtFile
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/OOXML /core/OOXML
COPY core/MsBinaryFile /core/MsBinaryFile
COPY --from=boost /usr/local/include/boost /usr/local/include/boost
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh TxtFile/Projects/Linux
# Outputs /core/build/lib/linux_64/libTxtXmlFormatLib.a



FROM base AS bindocument
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/Common /core/Common
COPY core/MsBinaryFile /core/MsBinaryFile
COPY core/OfficeUtils /core/OfficeUtils
COPY core/OfficeCryptReader /core/OfficeCryptReader
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/HtmlFile /core/HtmlFile
COPY core/HtmlFile2 /core/HtmlFile2
COPY core/RtfFile /core/RtfFile
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh OOXML/Projects/Linux/BinDocument
# Outputs /core/build/lib/linux_64/libBinDocument.a


FROM base AS docxformatlib
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh OOXML/Projects/Linux/DocxFormatLib
RUN cp /core/libDocxFormatLib.a /core/build/lib/linux_64/
# Outputs /core/build/lib/linux_64/libDocxFormatLib.a


FROM base AS pptxformatlib
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/Common /core/Common
COPY core/MsBinaryFile /core/MsBinaryFile
COPY core/OfficeUtils /core/OfficeUtils
COPY core/OfficeCryptReader /core/OfficeCryptReader
COPY core/UnicodeConverter /core/UnicodeConverter
COPY --from=boost /usr/local/include/boost /usr/local/include/boost
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh OOXML/Projects/Linux/PPTXFormatLib
# Outputs /core/build/lib/linux_64/libPPTXFormatLib.a


FROM base AS xlsbformatlib
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/Common /core/Common
COPY core/MsBinaryFile /core/MsBinaryFile
COPY core/OfficeCryptReader /core/OfficeCryptReader
COPY core/UnicodeConverter /core/UnicodeConverter
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh OOXML/Projects/Linux/XlsbFormatLib
# Outputs build/lib/linux_64/libXlsbFormatLib.a



FROM base AS vbaformatlib
COPY core/MsBinaryFile /core/MsBinaryFile
COPY core/Common /core/Common
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/OfficeCryptReader /core/OfficeCryptReader
COPY core/UnicodeConverter /core/UnicodeConverter
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh MsBinaryFile/Projects/VbaFormatLib/Linux
# Outputs build/lib/linux_64/libVbaFormatLib.a



FROM base AS docformatlib
COPY core/MsBinaryFile /core/MsBinaryFile
COPY core/Common /core/Common
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/OfficeCryptReader /core/OfficeCryptReader
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/OfficeUtils /core/OfficeUtils
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh MsBinaryFile/Projects/DocFormatLib/Linux
# Outputs build/lib/linux_64/libDocFormatLib.a



FROM base AS pptformatlib
COPY core/MsBinaryFile /core/MsBinaryFile
COPY core/Common /core/Common
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/OfficeCryptReader /core/OfficeCryptReader
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/OfficeUtils /core/OfficeUtils
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh MsBinaryFile/Projects/PPTFormatLib/Linux
# Outputs build/lib/linux_64/libPptFormatLib.a


FROM base AS build
COPY core /core
WORKDIR /core

# ENV DEV_MODE=on


# Link zlib into Common instead of including it in the build
RUN sed -i -e 's/build_all_zlib//' \
    Common/kernel.pro
RUN sed -i -e 's/build_zlib_as_sources//' \
    Common/kernel.pro

# Do not include zlib in the build, but link it later
RUN sed -i -e 's,$$OFFICEUTILS_PATH/src/zlib[^ ]*\.c,,' \
    DesktopEditor/graphics/pro/raster.pri
RUN sed -i -e 's,$$OFFICEUTILS_PATH/src/zlib[^ ]*\.c,,' \
    DesktopEditor/graphics/pro/freetype.pri


# TODO
# Do not include freetype in the build, but link it later
#RUN sed -i -e 's,$$FREETYPE_PATH/[^ ]*\.c,,' \
#    DesktopEditor/graphics/pro/freetype.pri

RUN embuild.sh MsBinaryFile/Projects/XlsFormatLib/Linux
RUN embuild.sh OdfFile/Projects/Linux
RUN embuild.sh RtfFile/Projects/Linux
RUN embuild.sh Common/cfcpp
RUN embuild.sh Common/3dParty/cryptopp/project
# RUN embuild.sh Fb2File
RUN embuild.sh Common/Network
RUN embuild.sh --no-sanitize PdfFile
# RUN embuild.sh HtmlFile2
# RUN embuild.sh EpubFile
# RUN embuild.sh XpsFile
# RUN embuild.sh DjVuFile
# RUN embuild.sh HtmlRenderer
RUN embuild.sh -q "CONFIG+=doct_renderer_empty" DesktopEditor/doctrenderer
RUN embuild.sh DocxRenderer

COPY pre-js.js /pre-js.js
COPY wrap-main.cpp /wrap-main.cpp

RUN cat /wrap-main.cpp >> /core/X2tConverter/src/main.cpp
RUN embuild.sh \
    -c -g \
    -l "-lgumbo" \
    -l "-lkatana" \
    -l "-L/usr/local/lib" \
    -l "--pre-js /pre-js.js" \
    -l "-sEXPORTED_RUNTIME_METHODS=ccall,FS" \
    -l "-sEXPORTED_FUNCTIONS=_main1" \
    -l "-sALLOW_MEMORY_GROWTH" \
    X2tConverter/build/Qt/X2tConverter.pro

WORKDIR /core/build/bin/linux_64/
RUN cp x2t x2t.js
RUN zip x2t.zip x2t.wasm x2t.js
RUN sha512sum x2t.zip > x2t.zip.sha512

WORKDIR /
RUN cp /core/build/bin/linux_64/x2t* .

COPY test.js /test.js




FROM build AS test
COPY tests /tests
RUN mkdir /results
RUN . /emsdk/emsdk_env.sh \
 && node test.js


FROM scratch AS test-output
COPY --from=test /results /


FROM scratch AS output
COPY --from=build /core/build/bin/linux_64/x2t x2t.js
COPY --from=build /core/build/bin/linux_64/x2t.wasm x2t.wasm
COPY --from=build /core/build/bin/linux_64/x2t.zip x2t.zip
COPY --from=build /core/build/bin/linux_64/x2t.zip.sha512 x2t.zip.sha512
