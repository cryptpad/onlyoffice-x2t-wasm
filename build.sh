#!/usr/bin/env bash

set -euxo pipefail

rm -rf results build
docker build --target test-output -o results .
docker build --target output -o build .
