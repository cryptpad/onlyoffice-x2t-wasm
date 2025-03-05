#!/usr/bin/env bash

set -euxo pipefail

docker build --format docker --target log-symbols-output -o log-symbols .
