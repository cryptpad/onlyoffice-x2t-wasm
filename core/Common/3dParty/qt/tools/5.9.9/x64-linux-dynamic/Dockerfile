FROM ubuntu:18.04 AS qt-builder

    # Prevent interactive prompts
    ENV DEBIAN_FRONTEND=noninteractive

    # Install build dependencies for 18.04
    # Note: python-is-python3 doesn't exist here, so we link it manually
    RUN apt-get update && apt-get install -y \
        build-essential \
        wget \
        tar \
        python3 \
        python3-pip \
        pkg-config \
        libgstreamer1.0-dev \
        libgstreamer-plugins-base1.0-dev \
        libgl1-mesa-dev \
        libxcb1-dev \
        libdbus-1-dev \
        libicu-dev \
        libfreetype6-dev \
        libfontconfig1-dev \
        libharfbuzz-dev \
        #libxkbcommon-dev \
        #libxkbcommon-x11-dev \
        libxcb-xinput-dev \
        libsm-dev \
        libatspi2.0-dev \
        libglib2.0-dev \
        libxi-dev \
        libasound2-dev \
        libpulse-dev \
        #libssl-dev \
        #libssl1.0-dev \
        libcups2-dev \
        libgtk-3-dev \
        libxcomposite-dev \
        && ln -s /usr/bin/python3 /usr/bin/python \
        && rm -rf /var/lib/apt/lists/*

    WORKDIR /build

    # Download and extract
    RUN wget https://download.qt.io/archive/qt/5.9/5.9.9/single/qt-everywhere-opensource-src-5.9.9.tar.xz -O ./qt_source_5.9.9.tar.xz && \
        tar -xf ./qt_source_5.9.9.tar.xz && \
        rm ./qt_source_5.9.9.tar.xz

    WORKDIR /build/qt-everywhere-opensource-src-5.9.9

    # Configure
    # We can now use the original parameters from build_tools
    RUN ./configure \
        -opensource \
        -confirm-license \
        -release \
        -shared \
        -accessibility \
        -prefix ./../qt_build/Qt-5.9.9/gcc_64 \
        -qt-zlib \
        -qt-libpng \
        -qt-libjpeg \
        -qt-xcb \
        -qt-pcre \
        -no-sql-sqlite \
        -no-qml-debug \
        -gstreamer 1.0 \
        -nomake examples \
        -nomake tests \
        -skip qtenginio \
        -skip qtlocation \
        -skip qtserialport \
        -skip qtsensors \
        -skip qtxmlpatterns \
        -skip qt3d \
        -skip qtwebview \
        -skip qtwebengine \
        # flags to match target build after comparison to onlyoffice build
        -dbus-linked \
        -icu \
        -no-iconv \
        -fontconfig \
        -system-freetype \
        -system-harfbuzz \
        -alsa \
        -pulseaudio \
        #-openssl-linked \
        -cups \
        -gtk

    # Build and install
    RUN make -j$(nproc)
    RUN make install

    RUN tar -cjf /qt_binary.tar.bz2 ./../qt_build/Qt-5.9.9

FROM scratch AS artifacts
    COPY --from=qt-builder /qt_binary.tar.bz2 /