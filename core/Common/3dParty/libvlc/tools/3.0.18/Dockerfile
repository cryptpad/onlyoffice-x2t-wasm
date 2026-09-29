FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    autoconf \
    automake \
    libtool \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build

# Clone repository
RUN git clone https://github.com/NixOS/patchelf.git patchelf_dir

WORKDIR /build/patchelf_dir

# Checkout specific tag
RUN git checkout tags/0.17.2

# Bootstrap and configure
RUN ./bootstrap.sh && \
    ./configure

# Patch Makefile.am to add static linking flags
RUN sed -i 's/^AM_CXXFLAGS = /AM_CXXFLAGS = -static-libstdc++ -static-libgcc /' ./src/Makefile.am

# Build
RUN make -j$(nproc)

WORKDIR /

RUN git clone https://code.videolan.org/videolan/vlc.git --depth 1 --branch 3.0.18 "/vlc" \
    || abort_op "Failed to clone depot_tools repo"

RUN sed -i 's|http://git.videolan.org/git/ffmpeg.git|https://github.com/FFmpeg/FFmpeg.git|' /vlc/contrib/src/ffmpeg/rules.mak

RUN cp ./build/patchelf_dir/src/patchelf /vlc

COPY ignore-cache-time.patch /vlc/ignore-cache-time.patch