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


FROM base AS apple3rdparty
COPY core/Common/3dParty/apple /core/Common/3dParty/apple
COPY --from=build-tools /build_tools/scripts/base.py /build_tools/scripts/
COPY --from=build-tools /build_tools/scripts/config.py /build_tools/scripts/
WORKDIR /core/Common/3dParty/apple
RUN python fetch.py
# Outputs: /core/Common/3dParty/apple



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
# TODO remove?
# WORKDIR /core/Common/3dParty/hyphen/hyphen
# RUN autoreconf -fvi
# RUN . /emsdk/emsdk_env.sh \
#  && emconfigure ./configure
# RUN . /emsdk/emsdk_env.sh \
#  && emmake make
# RUN . /emsdk/emsdk_env.sh \
#  && emmake make install
# outputs
# - /usr/local/lib/libhyphen.a
# - /usr/local/include/hyphen.h
# - /core/Common/3dParty/hyphen/hyphen/hnjalloc.h



FROM base as openssl
COPY core/Common/3dParty/openssl /core/Common/3dParty/openssl
WORKDIR /core/Common/3dParty/openssl/
RUN git clone --depth=1 --branch OpenSSL_1_1_1f https://github.com/openssl/openssl.git  # see build_tools/scripts/core_common/modules/openssl.py
WORKDIR /core/Common/3dParty/openssl/openssl
RUN ./config enable-md2 no-shared no-asm --prefix=/core/Common/3dParty/openssl/build/linux_64/ --openssldir=/core/Common/3dParty/openssl/build/linux_64/
RUN . /emsdk/emsdk_env.sh \
 && emmake make
RUN . /emsdk/emsdk_env.sh \
 && emmake make install

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
# For some reason ./configure wants to add `-lc` to the linker args. Use the config.cache to tell ./configure we do not want this.
RUN echo 'lt_cv_archive_cmds_need_lc=${lt_cv_archive_cmds_need_lc=no}' > config.cache
RUN . /emsdk/emsdk_env.sh \
 && emconfigure ./configure --config-cache
RUN . /emsdk/emsdk_env.sh \
 && emmake make
RUN . /emsdk/emsdk_env.sh \
 && emmake make install
# Outputs:
# - /usr/local/lib/libgumbo.a
# - /usr/local/include/gumbo.h



FROM base AS katana
WORKDIR /
RUN git clone https://github.com/jasenhuang/katana-parser.git
WORKDIR /katana-parser
RUN git checkout be6df4
RUN ./autogen.sh
# For some reason ./configure wants to add `-lc` to the linker args. Use the config.cache to tell ./configure we do not want this.
RUN echo 'lt_cv_archive_cmds_need_lc=${lt_cv_archive_cmds_need_lc=no}' > config.cache
RUN . /emsdk/emsdk_env.sh \
 && emconfigure ./configure --config-cache
RUN . /emsdk/emsdk_env.sh \
&& emmake make
RUN . /emsdk/emsdk_env.sh \
&& emmake make install
# Outputs:
# - /usr/local/lib/libkatana.a
# - /usr/local/include/katana.h


FROM base AS boost
# emscriptens boost does not work because of missing symbols
WORKDIR /
RUN git clone https://github.com/boostorg/boost.git
WORKDIR /boost
RUN git fetch && git checkout boost-1.84.0
RUN git submodule update --init --recursive
RUN . /emsdk/emsdk_env.sh \
 && CXXFLAGS=-fms-extensions emcmake cmake '-DBOOST_EXCLUDE_LIBRARIES=context;cobalt;coroutine;fiber;log;thread;wave;type_erasure;serialization;locale;contract;graph'
RUN . /emsdk/emsdk_env.sh \
 && emmake make
RUN . /emsdk/emsdk_env.sh \
 && emmake make install
RUN  cp -r /emsdk/upstream/emscripten/cache/sysroot/include/boost /usr/local/include/
RUN  cp /emsdk/upstream/emscripten/cache/sysroot/lib/libboost* /usr/local/lib/
# Outputs
# - /usr/local/include/boost
# - /usr/local/lib/libboost_*.a



FROM base AS unicodeconverter
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/DesktopEditor/common /core/DesktopEditor/common
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh UnicodeConverter
RUN mkdir -p /core/build/lib/linux_64
RUN mv /core/UnicodeConverter.o /core/build/lib/linux_64/libUnicodeConverter.a



FROM base AS common
COPY core/Common /core/Common
COPY core/DesktopEditor/common /core/DesktopEditor/common
COPY core/DesktopEditor/graphics /core/DesktopEditor/graphics
COPY core/DesktopEditor/xml /core/DesktopEditor/xml
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/OfficeUtils /core/OfficeUtils
COPY --from=unicodeconverter /core/build/lib/linux_64/ /core/build/lib/linux_64/
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
COPY --from=common /core/build/lib/linux_64/ /core/build/lib/linux_64/
COPY --from=katana /katana-parser /katana-parser
COPY --from=hyphen /core/Common/3dParty/hyphen/hyphen /core/Common/3dParty/hyphen/hyphen
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh -c "-Wno-register" DesktopEditor/graphics/pro
RUN ls -la /core/build/lib/linux_64/libgraphics.so
# Outputs /core/build/lib/linux_64/libgraphics.so


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
RUN mkdir -p /core/build/lib/linux_64/
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



FROM base AS xlsformatlib
COPY core/MsBinaryFile /core/MsBinaryFile
COPY core/Common /core/Common
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/OfficeCryptReader /core/OfficeCryptReader
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/OfficeUtils /core/OfficeUtils
COPY core/OdfFile /core/OdfFile
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh MsBinaryFile/Projects/XlsFormatLib/Linux
# Outputs build/lib/linux_64/libXlsFormatLib.a



FROM base AS odffile
COPY core/OdfFile /core/OdfFile
COPY core/Common /core/Common
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/OfficeCryptReader /core/OfficeCryptReader
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/OfficeUtils /core/OfficeUtils
COPY core/MsBinaryFile /core/MsBinaryFile
COPY core/PdfFile /core/PdfFile
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh OdfFile/Projects/Linux
# Outputs build/lib/linux_64/libOdfFormatLib.a



FROM base AS rtffile
COPY core/RtfFile /core/RtfFile
COPY core/Common /core/Common
COPY core/OdfFile /core/OdfFile
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/OfficeCryptReader /core/OfficeCryptReader
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/OfficeUtils /core/OfficeUtils
COPY core/MsBinaryFile /core/MsBinaryFile
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh RtfFile/Projects/Linux
# Outputs build/lib/linux_64/libRtfFormatLib.a



FROM base AS cfcpp
COPY core/Common /core/Common
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh Common/cfcpp
# Outputs build/lib/linux_64/libCompoundFileLib.a



FROM base AS cryptopp
COPY core/Common /core/Common
COPY core/OOXML /core/OOXML
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/OfficeCryptReader/ /core/OfficeCryptReader/
COPY core/MsBinaryFile /core/MsBinaryFile
COPY core/UnicodeConverter /core/UnicodeConverter
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh Common/3dParty/cryptopp/project
# Outputs build/lib/linux_64/libCryptoPPLib.a


FROM base AS network
COPY core/Common /core/Common
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/libkernel.so
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh Common/Network
# Outputs /core/build/lib/linux_64/libkernel_network.so



FROM base AS pdffile
COPY core/Common /core/Common
COPY core/PdfFile /core/PdfFile
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/OfficeUtils /core/OfficeUtils
COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/OOXML /core/OOXML
COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/
COPY --from=network /core/build/lib/linux_64/libkernel_network.so /core/build/lib/linux_64/
COPY --from=graphics /core/build/lib/linux_64/libgraphics.so /core/build/lib/linux_64/
COPY --from=unicodeconverter /core/build/lib/linux_64/libUnicodeConverter.a /core/build/lib/linux_64/
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh PdfFile
# Outputs /core/build/lib/linux_64/libPdfFile.so


FROM base AS doctrenderer
COPY core/DesktopEditor/ /core/DesktopEditor/
COPY core/Common /core/Common
COPY core/PdfFile /core/PdfFile
COPY core/OfficeUtils /core/OfficeUtils
# COPY core/UnicodeConverter /core/UnicodeConverter
COPY core/OOXML /core/OOXML
COPY core/XpsFile /core/XpsFile
COPY core/DjVuFile /core/DjVuFile
COPY core/DocxRenderer /core/DocxRenderer
# COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/
# COPY --from=network /core/build/lib/linux_64/libkernel_network.so /core/build/lib/linux_64/
# COPY --from=graphics /core/build/lib/linux_64/libgraphics.so /core/build/lib/linux_64/
# COPY --from=unicodeconverter /core/build/lib/linux_64/libUnicodeConverter.a /core/build/lib/linux_64/
COPY --from=openssl /core/Common/3dParty/openssl/ /core/Common/3dParty/openssl/
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh -s -q "CONFIG+=use_javascript_core" DesktopEditor/doctrenderer
# Outputs /core/build/lib/linux_64/



FROM base AS fb2file
COPY core/Fb2File/ /core/Fb2File/
COPY core/Common /core/Common
COPY core/DesktopEditor /core/DesktopEditor
COPY core/HtmlFile2 /core/HtmlFile2
COPY core/OfficeUtils /core/OfficeUtils
COPY core/UnicodeConverter /core/UnicodeConverter
COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/
COPY --from=graphics /core/build/lib/linux_64/libgraphics.so /core/build/lib/linux_64/
COPY --from=unicodeconverter /core/build/lib/linux_64/libUnicodeConverter.a /core/build/lib/linux_64/
COPY --from=gumbo /gumbo-parser /gumbo-parser
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh Fb2File
# Outputs /core/build/lib/linux_64/libFb2File.so



FROM base AS htmlfile2
COPY core/Common /core/Common
COPY core/DesktopEditor /core/DesktopEditor
COPY core/HtmlFile2 /core/HtmlFile2
COPY core/UnicodeConverter /core/UnicodeConverter
COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/
COPY --from=network /core/build/lib/linux_64/libkernel_network.so /core/build/lib/linux_64/
COPY --from=graphics /core/build/lib/linux_64/libgraphics.so /core/build/lib/linux_64/
COPY --from=unicodeconverter /core/build/lib/linux_64/libUnicodeConverter.a /core/build/lib/linux_64/
COPY --from=gumbo /gumbo-parser /gumbo-parser
COPY --from=katana /katana-parser /katana-parser
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh HtmlFile2
# Outputs /core/build/lib/linux_64/libHtmlFile2.so



FROM base AS epubfile
COPY core/EpubFile /core/EpubFile
COPY core/Common /core/Common
COPY core/DesktopEditor /core/DesktopEditor
COPY core/OfficeUtils /core/OfficeUtils
COPY core/HtmlFile2 /core/HtmlFile2
COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/
COPY --from=graphics /core/build/lib/linux_64/libgraphics.so /core/build/lib/linux_64/
COPY --from=htmlfile2 /core/build/lib/linux_64/libHtmlFile2.so /core/build/lib/linux_64/
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh EpubFile
# Outputs /core/build/lib/linux_64/libEpubFile.so



FROM base AS xpsfile
COPY core/XpsFile /core/XpsFile
COPY core/Common /core/Common
COPY core/DesktopEditor /core/DesktopEditor
COPY core/OfficeUtils /core/OfficeUtils
COPY core/PdfFile /core/PdfFile
COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/
COPY --from=graphics /core/build/lib/linux_64/libgraphics.so /core/build/lib/linux_64/
COPY --from=unicodeconverter /core/build/lib/linux_64/libUnicodeConverter.a /core/build/lib/linux_64/
COPY --from=pdffile /core/build/lib/linux_64/libPdfFile.so /core/build/lib/linux_64/
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh XpsFile
# Outputs /core/build/lib/linux_64/libXpsFile.so



FROM base AS djvufile
COPY core/DjVuFile /core/DjVuFile
COPY core/Common /core/Common
COPY core/DesktopEditor /core/DesktopEditor
COPY core/PdfFile /core/PdfFile
COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/
COPY --from=graphics /core/build/lib/linux_64/libgraphics.so /core/build/lib/linux_64/
COPY --from=unicodeconverter /core/build/lib/linux_64/libUnicodeConverter.a /core/build/lib/linux_64/
COPY --from=pdffile /core/build/lib/linux_64/libPdfFile.so /core/build/lib/linux_64/
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh DjVuFile
# Outputs /core/build/lib/linux_64/libDjVuFile.so



FROM base AS apple
COPY core/Apple /core/Apple
COPY core/Common /core/Common
COPY core/DesktopEditor /core/DesktopEditor
COPY core/OfficeUtils /core/OfficeUtils
COPY --from=apple3rdparty /core/Common/3dParty/apple /core/Common/3dParty/apple
COPY --from=boost /boost/libs/serialization/include/boost/archive/iterators/ /boost/libs/functional/include/boost/archive/iterators/
COPY --from=boost /boost/libs/serialization/include/boost/serialization/throw_exception.hpp /boost/libs/functional/include/boost/serialization/throw_exception.hpp
COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/
COPY --from=unicodeconverter /core/build/lib/linux_64/libUnicodeConverter.a /core/build/lib/linux_64/
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh Apple
# Outputs /core/build/lib/linux_64/libIWorkFile.so



FROM base AS hwpfile
COPY core/HwpFile /core/HwpFile
COPY core/Common /core/Common
COPY core/DesktopEditor /core/DesktopEditor
COPY core/OfficeUtils /core/OfficeUtils
COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/
COPY --from=unicodeconverter /core/build/lib/linux_64/libUnicodeConverter.a /core/build/lib/linux_64/
COPY --from=graphics /core/build/lib/linux_64/libgraphics.so /core/build/lib/linux_64/
COPY --from=cryptopp /core/build/lib/linux_64/libCryptoPPLib.a /core/build/lib/linux_64/
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh HwpFile
# Outputs /core/build/lib/linux_64/libHWPFile.so



FROM base AS docxrenderer
COPY core/DocxRenderer /core/DocxRenderer
COPY core/Common /core/Common
COPY core/DesktopEditor /core/DesktopEditor
COPY core/OfficeUtils /core/OfficeUtils
COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/
COPY --from=unicodeconverter /core/build/lib/linux_64/libUnicodeConverter.a /core/build/lib/linux_64/
COPY --from=graphics /core/build/lib/linux_64/libgraphics.so /core/build/lib/linux_64/
# COPY --from=cryptopp /core/build/lib/linux_64/libCryptoPPLib.a /core/build/lib/linux_64/
WORKDIR /core
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh DocxRenderer
# Outputs /core/build/lib/linux_64/libDocxRenderer.so



FROM base AS build
COPY core /core
WORKDIR /core

# ENV DEV_MODE=on


# TODO remove?
# Link zlib into Common instead of including it in the build
#RUN sed -i -e 's/build_all_zlib//' \
#    Common/kernel.pro
#RUN sed -i -e 's/build_zlib_as_sources//' \
#    Common/kernel.pro
#
## Do not include zlib in the build, but link it later
#RUN sed -i -e 's,$$OFFICEUTILS_PATH/src/zlib[^ ]*\.c,,' \
#    DesktopEditor/graphics/pro/raster.pri
#RUN sed -i -e 's,$$OFFICEUTILS_PATH/src/zlib[^ ]*\.c,,' \
#    DesktopEditor/graphics/pro/freetype.pri


# TODO
# Do not include freetype in the build, but link it later
#RUN sed -i -e 's,$$FREETYPE_PATH/[^ ]*\.c,,' \
#    DesktopEditor/graphics/pro/freetype.pri

# RUN embuild.sh Fb2File
# RUN embuild.sh HtmlFile2
# RUN embuild.sh EpubFile
# RUN embuild.sh XpsFile
# RUN embuild.sh DjVuFile
# RUN embuild.sh HtmlRenderer

# RUN embuild.sh DocxRenderer

COPY pre-js.js /pre-js.js
COPY wrap-main.cpp /wrap-main.cpp

COPY --from=gumbo /usr/local/lib/libgumbo.a /core/build/lib/linux_64/
COPY --from=katana /usr/local/lib/libkatana.a /core/build/lib/linux_64/
COPY --from=vbaformatlib /core/build/lib/linux_64/libVbaFormatLib.a /core/build/lib/linux_64/
COPY --from=odffile /core/build/lib/linux_64/libOdfFormatLib.a /core/build/lib/linux_64/
COPY --from=docformatlib /core/build/lib/linux_64/libDocFormatLib.a /core/build/lib/linux_64/
COPY --from=pptformatlib /core/build/lib/linux_64/libPptFormatLib.a /core/build/lib/linux_64/
COPY --from=rtffile /core/build/lib/linux_64/libRtfFormatLib.a /core/build/lib/linux_64/
COPY --from=txtfile /core/build/lib/linux_64/libTxtXmlFormatLib.a /core/build/lib/linux_64/
COPY --from=bindocument /core/build/lib/linux_64/libBinDocument.a /core/build/lib/linux_64/
COPY --from=pptxformatlib /core/build/lib/linux_64/libPPTXFormatLib.a /core/build/lib/linux_64/
COPY --from=docxformatlib /core/build/lib/linux_64/libDocxFormatLib.a /core/build/lib/linux_64/
COPY --from=boost /usr/local/include/boost /usr/local/include/boost
COPY --from=xlsbformatlib /core/build/lib/linux_64/libXlsbFormatLib.a /core/build/lib/linux_64/
COPY --from=xlsformatlib /core/build/lib/linux_64/libXlsFormatLib.a /core/build/lib/linux_64/
COPY --from=cryptopp /core/build/lib/linux_64/libCryptoPPLib.a /core/build/lib/linux_64/
COPY --from=graphics /core/build/lib/linux_64/libgraphics.so /core/build/lib/linux_64/
COPY --from=common /core/build/lib/linux_64/libkernel.so /core/build/lib/linux_64/
COPY --from=unicodeconverter /core/build/lib/linux_64/libUnicodeConverter.a /core/build/lib/linux_64/
COPY --from=network /core/build/lib/linux_64/libkernel_network.so /core/build/lib/linux_64/
COPY --from=pdffile /core/build/lib/linux_64/libPdfFile.so /core/build/lib/linux_64/
COPY --from=boost /usr/local/lib/* /core/build/lib/linux_64/
COPY --from=cfcpp /core/build/lib/linux_64/libCompoundFileLib.a /core/build/lib/linux_64/
COPY --from=fb2file /core/build/lib/linux_64/libFb2File.so /core/build/lib/linux_64/
COPY --from=htmlfile2 /core/build/lib/linux_64/libHtmlFile2.so /core/build/lib/linux_64/
COPY --from=epubfile /core/build/lib/linux_64/libEpubFile.so /core/build/lib/linux_64/
COPY --from=xpsfile /core/build/lib/linux_64/libXpsFile.so /core/build/lib/linux_64/
COPY --from=djvufile /core/build/lib/linux_64/libDjVuFile.so /core/build/lib/linux_64/
COPY --from=apple /core/build/lib/linux_64/libIWorkFile.so /core/build/lib/linux_64/
COPY --from=hwpfile /core/build/lib/linux_64/libHWPFile.so /core/build/lib/linux_64/
COPY --from=docxrenderer /core/build/lib/linux_64/libDocxRenderer.so /core/build/lib/linux_64/

# wasm-ld: error: unable to find library -ldoctrenderer

RUN cat /wrap-main.cpp >> /core/X2tConverter/src/main.cpp
RUN --mount=type=cache,sharing=locked,target=/emsdk/upstream/emscripten/cache/ \
    embuild.sh \
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
