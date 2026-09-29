#!/bin/bash

install_dir="$1"

abort_op()
{
    rm -rf "$install_dir"
    echo "Hyphen aborted: $1" >&2
    exit 1
}

if [ $# -lt 1 ]
then
    echo "Needs 1 arguments: install_dir_path" >&2
    exit 1
fi

if [ -d $install_dir ]
then
    echo "Skipping Hyphen (done already)."
    exit 0
else
    mkdir -p "$install_dir" || abort_op "Failed to create install dir: [$install_dir]"
fi

echo "Fetching hyphen"
git clone https://github.com/hunspell/hyphen "$install_dir" \
    || abort_op "Failed to clone Hyphen repo"
echo "hyphen ready!"
