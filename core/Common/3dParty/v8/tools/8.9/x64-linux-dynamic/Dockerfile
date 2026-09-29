FROM ubuntu:22.04 AS v8-builder

    # 1. Install system dependencies required by depot_tools and V8
    # We need python3, git, curl, and build-essential at a minimum
    RUN apt-get update && apt-get install -y \
        bash \
        git \
        python3 \
        python3-pip \
        python3-distutils \
        python-is-python3 \
        lsb-release \
        sudo \
        curl \
        xz-utils \
        pkg-config \
        build-essential \
        libstdc++6 \
        libglib2.0-dev \
        && rm -rf /var/lib/apt/lists/*
        
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