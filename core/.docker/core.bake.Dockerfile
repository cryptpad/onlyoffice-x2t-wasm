# ==============================================================================
# MODULE DOCKERFILE
# This file is not meant to be built standalone. It is consumed by the 
# docker-bake.hcl files in the parent monorepos.
# ==============================================================================

ARG NUGET_CACHE=local
ARG BUILD_ROOT
ARG NUGET_SOURCE_PATH

#### VCPKG BASE ####
FROM ubuntu:22.04 AS vcpkg-base

    # Avoid interactive prompts during package install
    ENV DEBIAN_FRONTEND=noninteractive

    # Install system dependencies
    RUN apt-get update && apt-get install -y \
        ca-certificates \
        git \
        curl \
        zip \
        unzip \
        tar \
        build-essential \
        pkg-config \
        cmake \
        ninja-build \
        mono-devel \
        && rm -rf /var/lib/apt/lists/*

    # Install vcpkg
    WORKDIR /opt
    RUN git clone https://github.com/microsoft/vcpkg.git \
        && cd vcpkg \
        && ./bootstrap-vcpkg.sh

    # Make vcpkg available globally
    ENV VCPKG_ROOT=/opt/vcpkg
    ENV PATH="${VCPKG_ROOT}:${PATH}"

    ENV VCPKG_BINARY_SOURCES="clear;nuget,NuGetCache,readwrite;nugettimeout,3600"


FROM vcpkg-base AS vcpkg-local

    RUN vcpkg fetch nuget && \
        mkdir /nuget-cache && \
        mono $(vcpkg fetch nuget) sources add \
            -Source "/nuget-cache" \
            -Name "NuGetCache"


FROM vcpkg-base AS vcpkg-remote

    ARG NUGET_REMOTE_URL
    ARG NUGET_USERNAME
    ARG NUGET_PASSWORD

    RUN vcpkg fetch nuget && \
        mono $(vcpkg fetch nuget) sources add \
            -Source "${NUGET_REMOTE_URL}" \
            -Name "NuGetCache" \
            -Username "${NUGET_USERNAME}" \
            -Password "${NUGET_PASSWORD}" \
            -StorePasswordInClearText



#### CORE BASE ####
# Build on Ubuntu 22.04 (Jammy, glibc 2.35) so the output binaries never
# reference glibc symbols newer than 2.35.  This covers Debian 12 (glibc 2.36)
# and Rocky Linux 9 (glibc 2.34 — glibc 2.35 symbols are avoided in practice
# as the code does not call any functions first introduced in 2.35).
# libstdc++ and libgcc are statically linked via -static-libstdc++ -static-libgcc
# (see common.cmake) so the GLIBCXX version on the target system is irrelevant.
# glibc itself cannot be statically linked into shared libraries, hence the
# old Ubuntu base remains necessary.
FROM vcpkg-${NUGET_CACHE} AS core-base
    ARG BUILD_ROOT=/package
    ARG TARGETARCH

    ENV TZ=Etc/UTC
    ENV DEBIAN_FRONTEND=noninteractive

    # cmake from ubuntu noble is 3.28.x; vcpkg now requires >=4.x.
    # Install cmake 4.x from Kitware's apt repo here (after vcpkg bootstrap)
    # so the vcpkg-base git-clone+bootstrap layer remains cacheable even when
    # GitHub CDN is unreachable in network-restricted build environments.
    RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone && \
        apt-get update && \
        DEBIAN_FRONTEND=noninteractive apt-get install -y \
            git curl sudo wget ssh gpg \
            build-essential make ninja-build pkg-config \
            libglib2.0-dev \
            python3 python-is-python3 python3-venv python3-setuptools \
            python3-httplib2 \
            lsb-release autoconf automake libtool findutils \
            gn \
        #&& curl -fsSL https://apt.kitware.com/keys/kitware-archive-latest.asc \
        #    | gpg --dearmor -o /etc/apt/keyrings/kitware.gpg \
        #&& echo "deb [signed-by=/etc/apt/keyrings/kitware.gpg] https://apt.kitware.com/ubuntu/ noble main" \
        #    > /etc/apt/sources.list.d/kitware.list \
        #&& apt-get update && apt-get install -y cmake \
        && rm -rf /var/lib/apt/lists/*

    # clang-13 required for V8 9.x — only available on jammy (22.04), not noble (24.04)
    RUN wget -qO - https://apt.llvm.org/llvm-snapshot.gpg.key | \
        gpg --dearmor -o /etc/apt/keyrings/llvm-snapshot.gpg && \
        echo "deb [signed-by=/etc/apt/keyrings/llvm-snapshot.gpg] http://apt.llvm.org/jammy/ llvm-toolchain-jammy-13 main" \
        > /etc/apt/sources.list.d/llvm-13.list && \
        apt-get update && apt-get install -y \
            clang-13 lld-13 llvm-13-dev llvm-13 \
            libc++-13-dev libc++abi-13-dev \
            qemu-user-static binfmt-support && \
        rm -rf /var/lib/apt/lists/*

    # set clang 13 as standard
    RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-13 100 && \
        update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-13 100 && \
        update-alternatives --install /usr/bin/llvm-ar llvm-ar /usr/bin/llvm-ar-13 100 && \
        update-alternatives --install /usr/bin/llvm-nm llvm-nm /usr/bin/llvm-nm-13 100 && \
        update-alternatives --install /usr/bin/llvm-ranlib llvm-ranlib /usr/bin/llvm-ranlib-13 100 && \
        update-alternatives --install /usr/bin/lld lld /usr/bin/lld-13 100


    ENV PATH="/root/.cargo/bin:${PATH}"

    # Git needs to allow repo paths copied by Docker
    RUN git config --global --add safe.directory '*'

    # upstream behavior — unchanged
    COPY core /core

    ENV BUILD_ROOT=${BUILD_ROOT}


#### CORE ####
FROM core-base AS core
    ARG NUGET_SOURCE_PATH
    ARG TARGETARCH
    RUN --mount=type=cache,target=/build-cache \
        --mount=type=bind,source=${NUGET_SOURCE_PATH},target=/nuget-cache,rw \
        mkdir -p ${BUILD_ROOT} && \
        cd /build-cache && \
        cmake -GNinja \
        -DVCPKG_MANIFEST_MODE=ON \
        -DVCPKG_MANIFEST_DIR=/core \
        -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_CXX_FLAGS_RELEASE="-O3 -w" \
        -DCMAKE_C_FLAGS_RELEASE="-O3 -w" \
        -DEO_CORE_OUTPUT_DIR=/build-cache/package/bin \
        -DEO_CORE_TOOLS_DIR=/build-cache/package/tools \
        /core && \
        cmake --build . && \
        cp -r package/* ${BUILD_ROOT}
