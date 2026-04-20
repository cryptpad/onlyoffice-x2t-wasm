#!/usr/bin/env bash

set -euxo pipefail

DOCKER_LOG=$(mktemp)

docker build . 2>&1 | tee $DOCKER_LOG

IMAGE_ID=$(grep --max-count=1 "writing image" $DOCKER_LOG | sed -e 's/^.*\(sha256:[0-9a-f]*\) .*$/\1/')

rm -rf results
mkdir results

# docker run -it -p 9229:9229 -v $PWD/tests/:/tests/ -v $PWD/results/:/results/ $IMAGE_ID

rm -rf build
mkdir build

CONTAINER_ID=$(docker create "$IMAGE_ID")
docker cp "$CONTAINER_ID:/core/build/bin/linux_64/x2t" build/x2t.js
docker cp "$CONTAINER_ID:/core/build/bin/linux_64/x2t.wasm" build/
# docker cp "$CONTAINER_ID:/core/build/bin/linux_64/x2t.wasm.map" build/
docker rm "$CONTAINER_ID"
