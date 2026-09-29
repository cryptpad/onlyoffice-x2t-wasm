#!/bin/bash

work_dir="$1"
install_dir="$2"
keep_work=${3:-0}

abort_op()
{
    rm -rf "$work_dir"
    rm -rf "$install_dir"
    echo "OpenSSL aborted: $1" >&2
    exit 1
}

if [ $# -lt 2 ]
then
    echo "Needs 2 arguments: work_dir_path install_dir_path" >&2
    exit 1
fi

if [ -d $install_dir ]
then
    echo "Skipping OpenSSL (done already)."
    exit 0
else
    mkdir -p "$install_dir" || abort_op "Failed to create install dir: [$install_dir]"
fi

if [ -d "$work_dir" ]
then
    rm -rf $work_dir
fi
mkdir -p "$work_dir" || abort_op "Failed to create work dir: [$work_dir]"

echo "Fetching OpenSSL repo into: [$work_dir]"
git clone --depth=1 --branch OpenSSL_1_1_1f https://github.com/openssl/openssl.git "$work_dir" \
    || abort_op "Git clone failed!"

echo "Building OpenSSL"
cd "$work_dir"
./config enable-md2 no-shared no-asm --prefix=$install_dir --openssldir=$install_dir \
    || abort_op "Configuration failed!"

make -j10 || abort_op "Build failed!"

echo "Installing OpenSSL to: [$install_dir]"
make install || abort_op "Install failed!"

if [ "$keep_work" -eq 0 ]; then
    echo "OpenSSL ready! (work dir will be removed)"
    rm -rf "$work_dir"
fi

exit 0
