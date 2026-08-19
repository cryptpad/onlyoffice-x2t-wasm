#!/bin/bash

install_dir="$1"

script_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
patches_dir="$script_dir"

abort_op()
{
    rm -rf "$install_dir"
    echo "Apple aborted: $1" >&2
    exit 1
}

shallow_checkout_commit()
{
    repo_name="$1"
    repo_url=$2
    commit=$3

    mkdir -p "$install_dir/$repo_name" || abort_op "Failed to create $repo_name directory."
    cd "$install_dir/$repo_name"
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

if [ $# -lt 1 ]
then
    echo "Needs 1 arguments: install_dir_path" >&2
    exit 1
fi

if [ -d $install_dir ]
then
    echo "Skipping Apple (done already)."
    exit 0
else
    mkdir -p "$install_dir" || abort_op "Failed to create install dir: [$install_dir]"
fi

# glm
shallow_checkout_commit "glm" "https://github.com/g-truc/glm.git" 33b4a621a697a305bc3a7610d290677b96beb181

# mdds
shallow_checkout_commit "mdds" "https://github.com/kohei-us/mdds.git" 0783158939c6ce4b0b1b89e345ab983ccb0f0ad0
apply_patch "$install_dir/mdds" "$patches_dir/mdds.patch"

# librevenge
shallow_checkout_commit "librevenge" "https://github.com/Distrotech/librevenge.git" becd044b519ab83893ad6398e3cbb499a7f0aaf4
apply_patch "$install_dir/librevenge" "$patches_dir/librevenge.patch"

# libodfgen
shallow_checkout_commit "libodfgen" "https://github.com/Distrotech/libodfgen.git" 8ef8c171ebe3c5daebdce80ee422cf7bb96aa3bc

# libetonyek
shallow_checkout_commit "libetonyek" "https://github.com/LibreOffice/libetonyek.git" cb396b4a9453a457469b62a740d8fb933c9442c3
apply_patch "$install_dir/libetonyek" "$patches_dir/libetonyek.patch"

# fetch.py is called with use_gperf = False, so I won't bother with that now.
# see Common/3dParty/apple/fetch.py
