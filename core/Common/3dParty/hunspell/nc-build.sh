#!/bin/bash
set -e

HUNSPELL_DIR="$1"
APPLY_PATCHES="${2:-yes}"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

if [ ! -d "$HUNSPELL_DIR" ]; then
  git clone --depth=1 --branch v1.7.2 https://github.com/hunspell/hunspell.git $HUNSPELL_DIR

  if [ "$APPLY_PATCHES" == "yes" ]; then
    # patch
    git -C "${HUNSPELL_DIR}" apply --check "${SCRIPT_DIR}/patches/fix-wasm-hunspell.patch" && \
    git -C "${HUNSPELL_DIR}" apply "${SCRIPT_DIR}/patches/fix-wasm-hunspell.patch"
  fi
fi