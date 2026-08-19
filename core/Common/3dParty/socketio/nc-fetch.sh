#!/bin/bash

install_dir="$1"

script_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
patches_dir="$script_dir/patches/proper_patches"

abort_op()
{
    rm -rf "$install_dir"
    echo "Socket-IO aborted: $1" >&2
    exit 1
}

if [ $# -lt 1 ]
then
    echo "Needs 1 arguments: install_dir_path" >&2
    exit 1
fi

if [ -d $install_dir ]
then
    echo "Skipping Socket-IO (done already)."
    exit 0
else
    mkdir -p "$install_dir" || abort_op "Failed to create install dir: [$install_dir]"
fi

echo "Fetching Socket-IO"
mkdir -p "$install_dir" || abort_op "Failed to create Socket-IO directory."
cd "$install_dir"
git init || abort_op "Git init failed (Socket-IO)"
git remote add origin https://github.com/socketio/socket.io-client-cpp.git || abort_op "Failed to add Socket-IO remote"
git fetch --depth 1 origin da779141a7379cc30c870d48295033bc16a23c66 || abort_op "Failed to fetch da779141a7379cc30c870d48295033bc16a23c66"
git checkout FETCH_HEAD || abort_op "Check-out failed (Socket-IO)"

# git clone https://github.com/socketio/socket.io-client-cpp.git "$install_dir" \
#     || abort_op "Git clone failed!"

# cd "$install_dir"
# git checkout da779141a7379cc30c870d48295033bc16a23c66 || abort_op "Failed to checkout da779141a7379cc30c870d48295033bc16a23c66"
git submodule update --init --recursive || abort_op "Failed to update submodules"

echo "Patching socket-io submodules"
cd "$install_dir/lib/asio"
git checkout 230c0d2ae035c5ce1292233fcab03cea0d341264 || abort_op "Failed to checkout 230c0d2ae035c5ce1292233fcab03cea0d341264"

cd "$install_dir/lib/websocketpp"
git checkout 56123c87598f8b1dd471be83ca841ceae07f95ba || abort_op "Failed to checkout 56123c87598f8b1dd471be83ca841ceae07f95ba"
git apply "$patches_dir/websocketpp.patch" || abort_op "Failed to apply websocketpp.patch"

cd "$install_dir/src/internal"
git apply "$patches_dir/sio_client_impl_fail.patch" || abort_op "Failed to apply sio_client_impl_fail.patch"
git apply "$patches_dir/sio_client_impl_open.patch" || abort_op "Failed to apply sio_client_impl_open.patch"
git apply "$patches_dir/sio_client_impl_close_timeout.patch" || abort_op "Failed to apply sio_client_impl_close_timeout.patch"

cd "$install_dir"
cp -r "$install_dir/src" "$install_dir/src_no_tls"
git apply "$patches_dir/no_tls.patch" || abort_op "Failed to apply no_tls.patch"

echo "Socket-IO ready!"

exit 0
