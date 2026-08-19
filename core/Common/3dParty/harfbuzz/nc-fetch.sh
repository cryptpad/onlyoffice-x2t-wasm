#!/bin/bash

install_dir="$1"

script_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
patches_dir="$script_dir/patch"

abort_op()
{
    rm -rf "$install_dir"
    echo "Harfbuzz aborted: $1" >&2
    exit 1
}

if [ $# -lt 1 ]
then
    echo "Needs 1 arguments: install_dir_path" >&2
    exit 1
fi

if [ -d $install_dir ]
then
    echo "Skipping Harfbuzz (done already)."
    exit 0
else
    mkdir -p "$install_dir" || abort_op "Failed to create install dir: [$install_dir]"
fi

echo "Fetching Harfbuzz"

mkdir -p "$install_dir" || abort_op "Failed to create harfbuzz directory."
cd "$install_dir"
git init || abort_op "Git init failed (harfbuzz)"
git remote add origin https://github.com/harfbuzz/harfbuzz.git || abort_op "Failed to add harfbuzz remote"
git fetch --depth 1 origin 894a1f72ee93a1fd8dc1d9218cb3fd8f048be29a || abort_op "Failed to fetch 894a1f72ee93a1fd8dc1d9218cb3fd8f048be29a"
git checkout FETCH_HEAD || abort_op "Check-out failed (harfbuzz)"
git apply $patches_dir/harfbuzz.patch || abort_op "Failed to apply harfbuzz.patch"

echo "Harfbuzz ready!"
