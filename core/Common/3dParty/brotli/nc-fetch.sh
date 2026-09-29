#!/bin/bash

install_dir="$1"

abort_op()
{
    rm -rf "$install_dir"
    echo "Brotli aborted: $1" >&2
    exit 1
}

if [ $# -lt 1 ]
then
    echo "Needs 1 arguments: install_dir_path" >&2
    exit 1
fi

if [ -d $install_dir ]
then
    echo "Skipping Brotli (done already)."
    exit 0
else
    mkdir -p "$install_dir" || abort_op "Failed to create install dir: [$install_dir]"
fi

echo "Fetching Brotli"

mkdir -p "$install_dir" || abort_op "Failed to create brotli directory."
cd "$install_dir"
git init || abort_op "Git init failed (brotli)"
git remote add origin https://github.com/google/brotli.git || abort_op "Failed to add brotli remote"
git fetch --depth 1 origin a47d7475063eb223c87632eed806c0070e70da29 || abort_op "Failed to fetch a47d7475063eb223c87632eed806c0070e70da29"
git checkout FETCH_HEAD || abort_op "Check-out failed (brotli)"

echo "Brotli ready!"
