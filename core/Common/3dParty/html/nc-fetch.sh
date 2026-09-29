#!/bin/bash

install_dir_katana=$1
install_dir_gumbo=$2

script_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
patches_dir="$script_dir"

abort_op()
{
    rm -rf "$install_dir_katana"
    rm -rf "$install_dir_gumbo"
    echo "Katana & Gumbo aborted: $1" >&2
    exit 1
}

shallow_checkout_commit()
{
    repo_name="$1"
    repo_install_dir="$2"
    repo_url=$3
    commit=$4

    mkdir -p "$repo_install_dir" || abort_op "Failed to create $repo_name directory."
    cd "$repo_install_dir"
    git init || abort_op "Git init failed ($repo_name)"
    git remote add origin $repo_url || abort_op "Failed to add $repo_name remote"
    git fetch --depth 1 origin $commit || abort_op "Failed to fetch $commit"
    git checkout FETCH_HEAD || abort_op "Check-out failed ($repo_name)"
}

apply_patch()
{
    repo_path="$1"
    patch_path="$2"

    cd "$repo_path"
    git apply "$patch_path" || abort_op "Failed to apply $patch_path"
}

if [ $# -lt 2 ]
then
    echo "Needs 2 arguments: katana_install_dir_path gumbo_install_dir_path" >&2
    exit 1
fi

if [ -d $install_dir_katana ]
then
    echo "Skipping Katana (done already)."
    exit 0
else
    mkdir -p "$install_dir_katana" || abort_op "Failed to create install dir: [$install_dir_katana]"
fi

if [ -d $install_dir_gumbo ]
then
    echo "Skipping Gumbo (done already)."
    exit 0
else
    mkdir -p "$install_dir_gumbo" || abort_op "Failed to create install dir: [$install_dir_gumbo]"
fi


echo "Fetching Katana parser"
shallow_checkout_commit "katana-parser" "$install_dir_katana" "https://github.com/jasenhuang/katana-parser.git" be6df458d4540eee375c513958dcb862a391cdd1
apply_patch "$install_dir_katana" "$patches_dir/katana.patch"
echo "Katana ready!"

echo "Fetching Gumbo parser"
shallow_checkout_commit "gumbo-parser" "$install_dir_gumbo" "https://github.com/google/gumbo-parser.git" aa91b27b02c0c80c482e24348a457ed7c3c088e0
apply_patch "$install_dir_gumbo" "$patches_dir/gumbo.patch"

echo "Gumbo ready!"
