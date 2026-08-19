#!/usr/bin/env bash
set -Eeuo pipefail

if [ $# -lt 2 ]; then
  echo "Usage: $0 <work_dir> <install_dir>" >&2
  exit 1
fi

work_dir="$1"
install_dir="$2"
TARGETARCH="${TARGETARCH:-x64}"

# Normalize TARGETARCH early
case "$TARGETARCH" in
  aarch64)
    TARGETARCH="arm64"
    ;;
  x86_64|amd64)
    TARGETARCH="x64"
    ;;
esac

script_dir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
patches_dir="$script_dir"

log() { echo "[v8-build] $*"; }
abort_op() { echo "v8 aborted: $1" >&2; exit 1; }

retry() {
  local tries=$1; shift
  local n=1
  until "$@"; do
    if (( n >= tries )); then
      echo "Command failed after $n attempts: $*" >&2
      return 1
    fi
    sleep $((n*5))
    ((n++))
  done
}

# ---------- System Check ----------
log "Checking system requirements..."

if ! command -v git &> /dev/null; then
  abort_op "git not found - install with: apt-get install git"
fi

if ! command -v python3 &> /dev/null; then
  abort_op "python3 not found - install with: apt-get install python3"
fi

if ! command -v clang &> /dev/null; then
  abort_op "clang not found - install with: apt-get install clang lld"
fi

if ! command -v ninja &> /dev/null; then
  abort_op "ninja not found - install with: apt-get install ninja-build"
fi

mkdir -p "$work_dir" "$install_dir"
cd "$work_dir"

# ---------- Force bash as shell ----------
export SHELL=/bin/bash
export CONFIG_SHELL=/bin/bash

# ---------- depot_tools ----------
export DEPOT_TOOLS="$work_dir/depot_tools"
export PATH="$DEPOT_TOOLS:$PATH"
export VPYTHON_BYPASS="manually managed python not supported by chrome operations"
export GCLIENT_SUPPRESS_GIT_VERSION_WARNING=1
export GYP_CHROMIUM_NO_ACTION=1

if [ ! -d "$DEPOT_TOOLS" ]; then
  log "Cloning depot_tools..."
  retry 3 git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git "$DEPOT_TOOLS" \
    || abort_op "clone depot_tools failed"
fi

# Update depot_tools
cd "$DEPOT_TOOLS"
git pull origin main || log "depot_tools update failed (non-fatal)"
cd "$work_dir"

# ---------- fetch V8 ----------
V8_ROOT="$work_dir/v8"
V8_SRC="$V8_ROOT/v8"

mkdir -p "$V8_ROOT"
cd "$V8_ROOT"

# Clean up previous gclient state
rm -f .gclient .gclient_entries
rm -rf _bad_scm chromium.googlesource.com

if [ ! -d "v8" ]; then
    log "Cloning V8 8.9.45 (for OnlyOffice)..."
    retry 3 git clone https://chromium.googlesource.com/v8/v8.git v8 \
      || abort_op "git clone v8 failed"
    cd v8
    git checkout 8.9.45 || abort_op "Failed to checkout V8 8.9.45"
    cd ..
else
    log "V8 directory exists, resetting to clean state..."
    cd v8
    git reset --hard
    git clean -fdx
    git fetch origin
    git checkout 8.9.45 || abort_op "Failed to checkout V8 8.9.45"
    cd ..
fi

# Create .gclient configuration
cat > .gclient <<'EOF'
solutions = [
  {
    "name": "v8",
    "url": "https://chromium.googlesource.com/v8/v8.git",
    "deps_file": "DEPS",
    "managed": False,
    "custom_deps": {},
  },
]
target_os = ["linux"]
EOF

log "Syncing V8 dependencies..."

# Clean any uncommitted changes before sync
if [ -d "$V8_SRC" ]; then
  log "Cleaning V8 directories before sync..."
  git -C "$V8_SRC" reset --hard 2>/dev/null || true
  git -C "$V8_SRC" clean -fd 2>/dev/null || true
fi

if [ -d "$V8_SRC/third_party/jinja2" ]; then
  git -C "$V8_SRC/third_party/jinja2" reset --hard 2>/dev/null || true
  git -C "$V8_SRC/third_party/jinja2" clean -fd 2>/dev/null || true
fi

if [ -d "$DEPOT_TOOLS" ]; then
  git -C "$DEPOT_TOOLS" reset --hard 2>/dev/null || true
  git -C "$DEPOT_TOOLS" clean -fd 2>/dev/null || true
fi

retry 3 gclient sync --no-history --shallow \
  || abort_op "gclient sync failed"

cd "$V8_SRC"

# ---------- apply patches AFTER gclient sync ----------
apply_patch() {
  local dir="$1"
  local patch="$2"
  
  [ -f "$patch" ] || { log "Patch not found: $patch (skipping)"; return 0; }
  
  if git -C "$dir" apply --check "$patch" >/dev/null 2>&1; then
    log "Applying patch: $patch"
    git -C "$dir" apply "$patch"
  else
    log "Patch already applied or not applicable: $patch"
  fi
}

if [ -f "$patches_dir/gclient_paths.patch" ]; then
  apply_patch "$DEPOT_TOOLS" "$patches_dir/gclient_paths.patch"
fi

if [ -f "$patches_dir/jinja2.patch" ]; then
  apply_patch "$V8_SRC/third_party/jinja2" "$patches_dir/jinja2.patch"
fi

if [ -f "$patches_dir/buildgn.patch" ]; then
  apply_patch "$V8_SRC" "$patches_dir/buildgn.patch"
fi

# ---------- Disable gmock to avoid visibility errors ----------
log "Disabling gmock to avoid visibility errors..."

GMOCK_BUILD="$V8_SRC/testing/gmock/BUILD.gn"
if [ -f "$GMOCK_BUILD" ]; then
  # Replace the problematic source_set with an empty group
  cat > "$GMOCK_BUILD" <<'GMOCK_EOF'
# Copyright 2015 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# Disabled to avoid visibility issues with gtest_config
# V8 monolithic build doesn't need gmock

import("//build_overrides/build.gni")

group("gmock") {
  testonly = true
}

group("gmock_main") {
  testonly = true
}
GMOCK_EOF
  log "Disabled gmock target"
fi

# ---------- Disable cppgc to avoid build errors ----------
log "Disabling cppgc build..."

CPPGC_BUILD="$V8_SRC/src/heap/cppgc/BUILD.gn"
if [ -f "$CPPGC_BUILD" ]; then
  # Replace with minimal stub
  cat > "$CPPGC_BUILD" <<'CPPGC_EOF'
# Copyright 2020 the V8 project authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# Disabled to avoid ARM64 toolchain issues

import("//build/config/sanitizers/sanitizers.gni")
import("../../gni/v8.gni")

group("cppgc_base") {
  visibility = [ ":*" ]
}

group("cppgc_base_for_testing") {
  testonly = true
  visibility = [ ":*" ]
}
CPPGC_EOF
  log "Replaced cppgc BUILD.gn with stub"
fi

# ---------- GN Setup ----------
log "Building GN from source (finding compatible commit)..."

GN_SRC="$work_dir/gn-source"
rm -rf "$GN_SRC"
git clone https://gn.googlesource.com/gn "$GN_SRC" \
  || abort_op "Failed to clone GN"
cd "$GN_SRC"

# Finde letzten Commit ohne C++20 Features (starts_with, ends_with, ranges::)
log "Searching for last C++17-compatible GN commit..."
GN_BIN=""
while IFS= read -r commit; do
  git checkout -q "$commit" 2>/dev/null || continue
  if ! grep -rq \
    "std::ranges::\|\.starts_with(\|\.ends_with(\|std::span\b" \
    src/gn/*.cc src/gn/*.h 2>/dev/null; then
    log "Found compatible commit: $commit ($(git log -1 --format='%ci' $commit))"
    break
  fi
done < <(git log --format="%H" --before="2022-01-01")

CC=clang-13 CXX=clang++-13 python3 build/gen.py --no-last-commit-position

# Der Compiler sucht last_commit_position.h via -I. (= out/ Verzeichnis)
mkdir -p out
cat > out/last_commit_position.h <<'LCHEOF'
#pragma once
#define LAST_COMMIT_POSITION_NUM 0
#define LAST_COMMIT_POSITION "0 (unknown)"
LCHEOF

CC=clang-13 CXX=clang++-13 ninja -C out \
  || abort_op "Failed to build GN"

mkdir -p "$V8_SRC/buildtools/linux64"
cp out/gn "$V8_SRC/buildtools/linux64/gn-built" \
  || abort_op "GN binary not found after build"
GN_BIN="$V8_SRC/buildtools/linux64/gn-built"
log "Successfully built GN: $($GN_BIN --version)"

cd "$V8_SRC"

log "Using GN: $GN_BIN (version: $($GN_BIN --version 2>/dev/null || echo 'unknown'))"

log "Building for TARGETARCH: $TARGETARCH"

# ---------- Detect Clang ----------
CLANG_PATH=$(which clang)
CLANG_DIR=$(dirname "$(dirname "$CLANG_PATH")")

log "Detected Clang at: $CLANG_DIR"
log "Clang version: $(clang --version | head -n1)"

# ---------- GN ARGS ----------
GN_ARGS="
target_os=\"linux\"
target_cpu=\"$TARGETARCH\"
v8_target_cpu=\"$TARGETARCH\"

is_debug=false
is_component_build=false
is_official_build=false

is_clang=true
clang_base_path=\"$CLANG_DIR\"
clang_use_chrome_plugins=false

# Explicit compiler paths
cc=\"clang\"
cxx=\"clang++\"

use_sysroot=false
use_custom_libcxx=false

# Symbol and debug settings
symbol_level=0
strip_debug_info=true
enable_dsyms=false
treat_warnings_as_errors=false

# V8 core settings
v8_monolithic=true
v8_use_external_startup_data=false
v8_enable_i18n_support=false
v8_enable_webassembly=false
v8_enable_pointer_compression=true
v8_enable_sandbox=false

# Disable cppgc to avoid build issues
cppgc_enable_caged_heap=false
v8_enable_conservative_stack_scanning=false
cppgc_is_standalone=false

# Disable all testing infrastructure - CRITICAL for avoiding gmock/gtest issues
v8_enable_test_features=false
v8_enable_verify_heap=false
v8_enable_verify_predictable=false
build_with_chromium=false

# Explicitly disable test targets
v8_enable_backtrace=false
v8_enable_disassembler=false
v8_enable_object_print=false

# Additional stability flags
v8_use_snapshot=true
v8_enable_lazy_source_positions=false
v8_enable_gdbjit=false
v8_enable_vtunejit=false
v8_enable_handle_zapping=false

# Use system toolchain properly
use_gold=false
use_lld=true
"

OUTPUT_DIR="$V8_SRC/out.gn/${TARGETARCH}.release"

log "Resetting build directory: $OUTPUT_DIR"
rm -rf "$OUTPUT_DIR"

log "Generating GN files..."
log "GN command: $GN_BIN gen $OUTPUT_DIR"

"$GN_BIN" gen "$OUTPUT_DIR" --args="$GN_ARGS" || abort_op "gn gen failed"

log "Build configuration generated successfully"
log "Checking generated ninja files..."

if [ ! -f "$OUTPUT_DIR/build.ninja" ]; then
  abort_op "build.ninja not generated"
fi

log "Building v8_monolith..."

# Set up LLVM toolchain
export AR=llvm-ar
export NM=llvm-nm
export RANLIB=llvm-ranlib
export CC=clang
export CXX=clang++
export SHELL=/bin/bash

# Verify tools exist
for tool in llvm-ar llvm-nm llvm-ranlib clang clang++; do
  if ! command -v $tool &> /dev/null; then
    abort_op "$tool not found - install llvm and clang"
  fi
done

log "Toolchain:"
log "  CC=$CC ($(clang --version | head -n1))"
log "  CXX=$CXX"
log "  AR=$AR"
log "  SHELL=$SHELL"

# Build with reasonable parallelism
NJOBS=$(nproc 2>/dev/null || echo 4)
log "Building with $NJOBS parallel jobs..."

# Force ninja to use bash instead of sh
export NINJA_STATUS="[%f/%t] "

/bin/bash -c "ninja -C '$OUTPUT_DIR' -j '$NJOBS' v8_monolith" || abort_op "ninja build failed"

# ---------- Verify Build ----------
if [ ! -f "$OUTPUT_DIR/obj/libv8_monolith.a" ]; then
  abort_op "Build completed but libv8_monolith.a not found"
fi

LIBSIZE=$(du -h "$OUTPUT_DIR/obj/libv8_monolith.a" | cut -f1)
log "Built libv8_monolith.a (size: $LIBSIZE)"

# ---------- INSTALL ----------
log "Installing artifacts to: $install_dir"
mkdir -p "$install_dir"
mkdir -p "$install_dir/v8/include"

# CMakeLists.txt erwartet:
#   ${V8_INSTALL_DIR}/libv8_monolith.a
#   ${V8_INSTALL_DIR}/v8/          (include path 1)
#   ${V8_INSTALL_DIR}/v8/include/  (include path 2, wo v8.h liegt)

cp "$OUTPUT_DIR/obj/libv8_monolith.a" "$install_dir/" \
  || abort_op "Failed to copy monolith library"

cp -r "$V8_SRC/include/"* "$install_dir/v8/include/" \
  || abort_op "Failed to copy public headers"

# OnlyOffice braucht auch interne V8 Headers (src/base/sys-info.h etc.)
# Nur .h Dateien kopieren, keine .cc/.o Dateien
mkdir -p "$install_dir/v8/src"
find "$V8_SRC/src" -name "*.h" | while read -r f; do
  rel="${f#$V8_SRC/src/}"
  dest="$install_dir/v8/src/$rel"
  mkdir -p "$(dirname "$dest")"
  cp "$f" "$dest"
done
log "Copied internal V8 headers"

# Create pkg-config file
cat > "$install_dir/v8.pc" <<EOF
prefix=$install_dir
libdir=\${prefix}
includedir=\${prefix}/v8/include

Name: V8
Description: V8 JavaScript Engine
Version: 8.9.45
Libs: -L\${libdir} -lv8_monolith -pthread
Cflags: -I\${includedir}
EOF

log "======================================"
log "v8-build complete!"
log "======================================"
log "Library:  $install_dir/libv8_monolith.a"
log "Headers:  $install_dir/v8/include/"

log "======================================"
log "v8-build complete!"
log "======================================"
log "Library: $install_dir/lib/libv8_monolith.a"
log "Headers: $install_dir/include/"
log "Pkg-config: $install_dir/lib/v8.pc"
log ""
log "To use in your project:"
log "  export PKG_CONFIG_PATH=$install_dir/lib:\$PKG_CONFIG_PATH"
log "  g++ -o app app.cpp \$(pkg-config --cflags --libs v8.pc) -pthread"