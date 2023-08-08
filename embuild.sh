#!/usr/bin/bash

set -exo pipefail

POSITIONAL_ARGS=()

QMAKE_ARGS=""
J_ARG="-j 8"
QMAKE_LFLAGS="-s USE_ICU=1"
CFLAGS="-s STACK_SIZE=128kb"

if [ -n "$DEV_MODE" ]; then
  SANITIZE="-fsanitize=address -fsanitize=undefined -Wcast-align -Wover-aligned -sWARN_UNALIGNED=1"
  # SANITIZE="-fsanitize=undefined -Wcast-align -Wover-aligned -sWARN_UNALIGNED=1 -sSAFE_HEAP=1"
  QMAKE_LFLAGS+=" -sINITIAL_MEMORY=400MB"
fi

while [[ $# -gt 0 ]]; do
  case $1 in
    -q)
      QMAKE_ARGS+=" $2"
      shift # past argument
      shift # past value
      ;;
    -c)
      CFLAGS+=" $2"
      shift # past argument
      shift # past value
      ;;
    -l)
      QMAKE_LFLAGS+=" $2"
      shift # past argument
      shift # past value
      ;;
    -s)
      J_ARG=""
      shift # past argument
      ;;
    --no-sanitize)
      SANITIZE=""
      shift # past argument
      ;;
    *)
      POSITIONAL_ARGS+=("$1") # save positional arg
      shift # past argument
      ;;
  esac
done

pushd /emsdk
. emsdk_env.sh
popd

qmake \
    "QMAKE_CXXFLAGS_RELEASE -= -O2" \
    "QMAKE_CXXFLAGS_RELEASE *= -Os" \
    "QMAKE_CC=emcc" \
    "QMAKE_CFLAGS+=-s USE_ICU=1 $SANITIZE $CFLAGS" \
    "QMAKE_CXX=em++" \
    "QMAKE_CXXFLAGS+=-s USE_ICU=1 $SANITIZE $CFLAGS" \
    "QMAKE_LINK=em++" \
    "QMAKE_LFLAGS+=$QMAKE_LFLAGS $SANITIZE $CFLAGS" \
    "DEFINES+=__linux__ __WASM__ HAVE_UNISTD_H _RWSTD_NO_SETRLIMIT" \
    $QMAKE_ARGS \
    $POSITIONAL_ARGS

emmake make $J_ARG