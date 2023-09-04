FROM ubuntu:22.04
SHELL ["/bin/bash", "-c"]

# TODO remove libc++-dev
RUN apt update \
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
       libc++-dev

WORKDIR /
RUN git clone https://github.com/emscripten-core/emsdk.git
WORKDIR /emsdk
RUN git fetch -a \
 && git checkout 3.1.45
RUN ./emsdk install 3.1.45
RUN ./emsdk activate 3.1.45

RUN . /emsdk/emsdk_env.sh && qtchooser -install qt6 $(which qmake6)
ENV QT_SELECT=qt6

WORKDIR /
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

# emscriptens boost does not work because of missing symbols
WORKDIR /
RUN git clone --recurse-submodules https://github.com/boostorg/boost.git
WORKDIR /boost
RUN git fetch -a \
 && git checkout boost-1.83.0
RUN . /emsdk/emsdk_env.sh \
 && CXXFLAGS=-fms-extensions emcmake cmake '-DBOOST_EXCLUDE_LIBRARIES=wave;type_erasure;thread;serialization;program_options;log;locale;json;graph;contract;context;coroutine;fiber'

RUN . /emsdk/emsdk_env.sh \
 && emmake make
RUN . /emsdk/emsdk_env.sh \
 && emmake make install
RUN find / -iname "*date_time*"
RUN find / -iname "*regex*"
RUN exit 1

# Ideas taken from https://github.com/jedisct1/openssl-wasm
WORKDIR /
ADD https://www.openssl.org/source/openssl-3.1.2.tar.gz /
RUN tar xvfz openssl-*.tar.gz
WORKDIR /openssl-3.1.2
RUN . /emsdk/emsdk_env.sh \
 && env \
    CROSS_COMPILE="" \
    CFLAGS="-Os" \
    ./Configure \
    no-asm \
    no-async \
    no-egd \
    no-ktls \
    no-module \
    no-posix-io \
    no-secure-memory \
    no-shared \
    no-sock \
    no-stdio \
    no-threads \
    no-ui-console \
    no-weak-ssl-ciphers
RUN . /emsdk/emsdk_env.sh \
 && emmake make
RUN . /emsdk/emsdk_env.sh \
 && emmake make install

COPY core /core
WORKDIR /core

# ENV DEV_MODE=on

COPY embuild.sh /bin/embuild.sh

RUN embuild.sh UnicodeConverter
RUN embuild.sh Common

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

RUN embuild.sh DesktopEditor/graphics/pro

# Do not include freetype in the build, but link it later
RUN sed -i -e 's,$$FREETYPE_PATH/[^ ]*\.c,,' \
    DesktopEditor/graphics/pro/freetype.pri

RUN embuild.sh TxtFile/Projects/Linux
RUN embuild.sh OOXML/Projects/Linux/BinDocument
RUN embuild.sh OOXML/Projects/Linux/DocxFormatLib
RUN embuild.sh OOXML/Projects/Linux/PPTXFormatLib
RUN embuild.sh OOXML/Projects/Linux/XlsbFormatLib
RUN embuild.sh MsBinaryFile/Projects/VbaFormatLib/Linux
RUN embuild.sh MsBinaryFile/Projects/DocFormatLib/Linux
RUN embuild.sh MsBinaryFile/Projects/PPTFormatLib/Linux
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
# RUN embuild.sh -q "CONFIG+=doct_renderer_empty" -s DesktopEditor/doctrenderer
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

WORKDIR /
RUN cp /core/build/bin/linux_64/x2t* .
COPY test.js /test.js
EXPOSE 9229

# CMD . /emsdk/emsdk_env.sh \
#  && node --inspect-brk=0.0.0.0:9229 test.js
CMD . /emsdk/emsdk_env.sh \
 && node test.js
