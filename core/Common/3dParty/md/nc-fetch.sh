#!/bin/bash

install_dir="$1"

abort_op()
{
    rm -rf "$install_dir"
    echo "MD aborted: $1" >&2
    exit 1
}

if [ $# -lt 1 ]
then
    echo "Needs 1 arguments: install_dir_path" >&2
    exit 1
fi

if [ -d $install_dir ]
then
    echo "Skipping MD (done already)."
    exit 0
else
    mkdir -p "$install_dir" || abort_op "Failed to create install dir: [$install_dir]"
fi

echo "Fetching MD"
git clone https://github.com/mity/md4c.git "$install_dir" \
    || abort_op "Failed to clone MD repo"
cd "$install_dir"
git checkout 481fbfbdf72daab2912380d62bb5f2187d438408 || abort_op "Failed to check out 481fbfbdf72daab2912380d62bb5f2187d438408"

echo "MD ready!"
