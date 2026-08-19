FROM ubuntu:22.04 AS v8-builder
    ENV DEBIAN_FRONTEND=noninteractive
    ENV CC=clang-13
    ENV CXX=clang++-13

    # 1. Install system dependencies and Python 3.11
    RUN apt-get update && apt-get install -y software-properties-common && \
        add-apt-repository ppa:deadsnakes/ppa && \
        apt-get update && apt-get install -y \
        bash \
        git \
        python3.11 \
        python3.11-dev \
        python3.11-distutils \
        python3.11-venv \
        lsb-release \
        sudo \
        curl \
        wget \
        xz-utils \
        pkg-config \
        build-essential \
        ninja-build \
        libstdc++6 \
        libglib2.0-dev

    # 2. Install Pip specifically for Python 3.11
    RUN curl -sS https://bootstrap.pypa.io/get-pip.py | python3.11

    # 3. Install httplib2 for Python 3.11
    RUN python3.11 -m pip install httplib2

    # 4. Set Python 3.11 as the default 'python' and 'python3' command
    RUN ln -sf /usr/bin/python3.11 /usr/bin/python3 && \
        ln -sf /usr/bin/python3.11 /usr/bin/python

    # Install clang-13 and LLVM tools for V8 9.x build
    RUN mkdir -p /etc/apt/keyrings && \
        wget -qO - https://apt.llvm.org/llvm-snapshot.gpg.key | gpg --dearmor -o /etc/apt/keyrings/llvm-snapshot.gpg && \
        echo "deb [signed-by=/etc/apt/keyrings/llvm-snapshot.gpg] http://apt.llvm.org/jammy/ llvm-toolchain-jammy-13 main" \
            > /etc/apt/sources.list.d/llvm-13.list && \
        apt-get update && apt-get install -y \
            clang-13 lld-13 llvm-13-dev llvm-13 \
            libc++-13-dev libc++abi-13-dev \
            qemu-user-static binfmt-support && \
        rm -rf /var/lib/apt/lists/*


    # Set clang-13 as default
    RUN update-alternatives --install /usr/bin/clang clang /usr/bin/clang-13 100 && \
        update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-13 100 && \
        update-alternatives --install /usr/bin/llvm-ar llvm-ar /usr/bin/llvm-ar-13 100 && \
        update-alternatives --install /usr/bin/llvm-nm llvm-nm /usr/bin/llvm-nm-13 100 && \
        update-alternatives --install /usr/bin/llvm-ranlib llvm-ranlib /usr/bin/llvm-ranlib-13 100 && \
        update-alternatives --install /usr/bin/lld lld /usr/bin/lld-13 100 && \
        update-alternatives --set clang /usr/bin/clang-13 && \
        update-alternatives --set clang++ /usr/bin/clang++-13 && \
        update-alternatives --set lld /usr/bin/lld-13 && \
        update-alternatives --set llvm-ar /usr/bin/llvm-ar-13 && \
        update-alternatives --set llvm-nm /usr/bin/llvm-nm-13 && \
        update-alternatives --set llvm-ranlib /usr/bin/llvm-ranlib-13

    # Verify clang version
    RUN clang-13 --version && \
        clang --version && \
        clang-13 --version | head -n1 | grep -q "clang version 13" || exit 1 && \
        clang --version | head -n1 | grep -q "clang version 13" || exit 1
        
    # 2. Set up working directories
    WORKDIR /build-context
    COPY nc-build.sh nc-build.sh

    COPY ./jinja2.patch jinja2.patch
    COPY ./gclient_paths.patch gclient_paths.patch
    COPY ./buildgn.patch buildgn.patch
    COPY ./bootstrap.patch bootstrap.patch

    # Ensure the script is executable
    RUN chmod +x ./nc-build.sh

    # 3. Run the build script
    # Arguments: /tmp/v8_work (temp build files) and /opt/v8 (final destination)
    RUN ./nc-build.sh /tmp/v8_work /build/v8


    RUN tar -cjf /v8_binary.tar.bz2 /build/v8

FROM scratch AS artifacts
    COPY --from=v8-builder /v8_binary.tar.bz2 /
