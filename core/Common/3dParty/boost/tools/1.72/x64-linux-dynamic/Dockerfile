# Use a stable Ubuntu base (20.04 is appropriate for Boost 1.72.0)
FROM ubuntu:20.04 AS boost-builder

    # Prevent interactive prompts during apt-get install
    ENV DEBIAN_FRONTEND=noninteractive

    # Install essential build tools: GCC, Clang, libc++, and Git
    RUN apt-get update && apt-get install -y \
        build-essential \
        clang \
        libc++-dev \
        libc++abi-dev \
        git \
        && rm -rf /var/lib/apt/lists/*

    # Arguments
    ARG BOOST_VERSION=boost-1.72.0
    ARG USE_CLANG=0

    # Clone the Boost repository
    WORKDIR /src
    RUN git clone --recursive --depth=1 https://github.com/boostorg/boost.git boost_1_72_0 -b ${BOOST_VERSION}

    # Change to the Boost directory
    WORKDIR /src/boost_1_72_0

    # Run the build logic based on the USE_CLANG argument
    RUN set -ex; \
        if [ "$USE_CLANG" = "1" ]; then \
            echo "Building with Clang and libc++..." && \
            ./bootstrap.sh --with-libraries=filesystem,system,date_time,regex --with-toolset=clang && \
            ./b2 headers && \
            ./b2 --clean && \
            ./b2 --prefix=/build/linux_64 link=shared \
                cxxflags="-fPIC -stdlib=libc++" \
                linkflags="-stdlib=libc++" \
                define=_LIBCPP_ENABLE_CXX17_REMOVED_UNARY_BINARY_FUNCTION \
                install; \
        else \
            echo "Building with GCC..." && \
            ./bootstrap.sh --with-libraries=filesystem,system,date_time,regex && \
            ./b2 headers && \
            ./b2 --clean && \
            ./b2 --prefix=/build/linux_64 link=shared cxxflags="-fPIC" install; \
        fi

    RUN tar -cjf /boost_binary.tar.bz2 /build/linux_64

FROM scratch AS artifacts
    COPY --from=boost-builder /boost_binary.tar.bz2 /