#!/usr/bin/env bash

set -euxo pipefail

PARAMS=

if command -v podman >/dev/null 2>&1
then
  CMD=podman
  export BUILDAH_FORMAT=docker
  PARAMS="--jobs 2"
fi

if command -v docker >/dev/null 2>&1
then
  CMD=docker
fi

rm -rf results build
$CMD build $PARAMS --target test-output -o results .
$CMD build $PARAMS --target output -o build .
