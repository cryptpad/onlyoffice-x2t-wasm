# ==============================================================================
# MODULE DOCKERFILE
# This file is not meant to be built standalone. It is consumed by the 
# docker-bake.hcl files in the parent monorepos.
#
# REQUIRED CONTEXTS:
# - sdkjs: files from sdkjs
# ==============================================================================

#### CORE WASM ####
FROM ghcr.io/euro-office/emsdk:5.0.4 AS core-wasm
    ARG BUILD_ROOT
    ARG CACHE_BUST
    ARG NUGET_SOURCE_PATH

    ENV BUILD_ROOT=${BUILD_ROOT}

    COPY core /core

    # hash wasm has one dependency in sdkjs which we must copy here (TODO: fix this)
    COPY sdkjs/common/stringserialize.js /sdkjs/common/stringserialize.js

    ARG CACHE_BUST=5

    RUN --mount=type=cache,id=wasm-build-cache-${CACHE_BUST},target=/build-cache-wasm \
        --mount=type=bind,source=${NUGET_SOURCE_PATH},target=/nuget-cache,rw <<EOF
        set -e
        cd /build-cache-wasm

        emcmake cmake -DEO_CORE_OUTPUT_DIR=/build-cache-wasm/dist /core

        cmake --build . -- -j$(nproc)
        
        cp -a /build-cache-wasm/dist/. ${BUILD_ROOT}/
EOF