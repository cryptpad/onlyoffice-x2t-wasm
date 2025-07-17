#!/usr/bin/env bash

set -euxo pipefail

docker build --target test-output -o results .
docker build --target output -o build .
