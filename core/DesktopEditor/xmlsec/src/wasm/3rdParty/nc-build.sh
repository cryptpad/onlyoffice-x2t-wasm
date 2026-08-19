#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

WORK_DIR="$1"
INSTALL_DIR="$2"

if [ ! -d "$WORK_DIR" ]; then
  git clone --depth=1 --branch OpenSSL_1_1_1f https://github.com/openssl/openssl.git $WORK_DIR
fi

# patch
git -C "${WORK_DIR}" apply --check "${SCRIPT_DIR}/patches/fix-wasm-openssl.patch" && \
git -C "${WORK_DIR}" apply "${SCRIPT_DIR}/patches/fix-wasm-openssl.patch"

if [ -f "/opt/emsdk/emsdk_env.sh" ]; then
    source /opt/emsdk/emsdk_env.sh
else
    echo "Warning: /opt/emsdk/emsdk_env.sh not found, skipping source..."
fi

cd $WORK_DIR
emconfigure ./config no-shared no-asm no-threads no-dso enable-md2 --prefix=$INSTALL_DIR --openssldir=$INSTALL_DIR
sed -i 's|^CROSS_COMPILE.*$|CROSS_COMPILE=|g' Makefile
emmake make build_generated libcrypto.a libssl.a