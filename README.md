# Build OnlyOffice x2t for WebAssembly

## Modifications by CryptPad

This repository contains a modified copy of https://github.com/ONLYOFFICE/core.git in `/core`. These modifications are made to be able to compile `x2t` to WebAssembly.

## Build

This is a Dockerfile building OnlyOffice x2t in WebAssembly using emscripten.
Build it with:

``` shell
./build.sh
```

## Update to a new x2t version

This repository includes a clone of x2t in the `core` directory. You can pull a
new x2t release with:

``` shell
git subtree pull --prefix core https://github.com/ONLYOFFICE/core.git <TAG> --squash
```

Since the clone contains small changes there may be merge conflicts.
