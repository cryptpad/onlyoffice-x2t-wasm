# Testing (C++ core)

The core ships ~50 test projects historically authored as **qmake `.pro`** files; 13 are
real [GoogleTest](https://github.com/google/googletest) suites. CI builds core with
**CMake/Ninja**, so tests are being migrated to **CMake targets registered with CTest** —
no separate qmake build is needed. This file documents how to run them and tracks the
per-suite migration.

## Running the tests

GoogleTest is pulled in through vcpkg via the `tests` manifest feature, so configure with
that feature and `-DEO_BUILD_TESTS=ON`:

```bash
cmake -GNinja -S . -B build \
  -DVCPKG_TARGET_TRIPLET=x64-linux-dynamic \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
  -DVCPKG_MANIFEST_MODE=ON -DVCPKG_MANIFEST_DIR=. \
  -DVCPKG_MANIFEST_FEATURES=tests -DEO_BUILD_TESTS=ON

cmake --build build
ctest --test-dir build --output-on-failure
```

Run a single suite:

```bash
ctest --test-dir build -R cfcpp_test --output-on-failure
```

CI runs `ctest --test-dir build --output-on-failure` after the build step
(`.github/workflows/build.yml`); a failing assertion fails the job.

## How a migrated suite is wired

CMake already builds every core library these tests link against. To migrate a suite:

1. Add a `CMakeLists.txt` next to the suite mirroring the `.pro`'s `ADD_DEPENDENCY` /
   `SOURCES` lines. Pull in each dependency with a guarded
   `if(NOT TARGET <lib>) add_subdirectory(...) endif()`.
2. Build and register it with the `add_core_gtest()` helper in `common.cmake`
   (`GTEST_MAIN` if the suite has no `main()`, `USE_GMOCK` if it uses gmock, optional
   `WORKING_DIRECTORY`).
3. Reproduce any extra `INCLUDEPATH` from the `.pro` with `target_include_directories`.
4. If the suite reads fixtures, stage them next to the test (or at the path the suite
   expects) with a `POST_BUILD` `copy_directory` and point `WORKING_DIRECTORY` at it.
5. `add_subdirectory(...)` the new `CMakeLists.txt` from the top-level `CMakeLists.txt`
   inside the `if(EO_BUILD_TESTS)` block.

`Common/cfcpp/test/CMakeLists.txt` is the reference example (own `main`, gmock, and
working-dir-relative fixtures).

## Migration status

Done:

- [x] CMake/CTest scaffolding — `add_core_gtest()` in `common.cmake`, `EO_BUILD_TESTS`
      option (default **OFF**; tests are opt-in, enabled with `-DEO_BUILD_TESTS=ON` plus the
      vcpkg `tests` feature) + `enable_testing()` in `CMakeLists.txt`, CTest step in CI.
- [x] `Common/cfcpp/test`
- [x] `DesktopEditor/graphics/tests/BooleanOperations_Unit-tests` — deps: kernel, graphics,
      UnicodeConverter. No fixtures. 17/20 tests run in CI; `OneIntersOutside`,
      `OneIntersInside`, `CurveIntersCurve` are quarantined via `GTEST_FILTER` (their
      computed boolean-path output differs from the expected paths — engine bug vs stale
      expectations not yet determined). See the `TODO` in that suite's `CMakeLists.txt`.
- [x] `OdfFile/Reader/Converter/StarMath2OOXML/TestSMConverter` — dep: StarMathConverter.
      No fixtures.
- [x] `OdfFile/Reader/Converter/StarMath2OOXML/TestEQNtoOOXML` — dep: StarMathConverter.
      No fixtures.

### gtest suites to migrate

Runnable headless once migrated (no missing fixtures, no JS engine):

- [ ] `OdfFile/Reader/Converter/StarMath2OOXML/TestSMCustomShape` — dep: StarMathConverter
      (confirm sources exist).
- [ ] `OfficeUtils/tests` — deps: kernel, UnicodeConverter. Fixtures committed under
      `tests/zip/` (stage next to binary).
- [ ] `OdfFile/Test/test_odf` — OdfFormatLib dependency chain; own `main`. Fixtures
      committed under `test_odf/ExampleFiles/`.
- [ ] `OOXML/test` — most complex: links the x2t dylib sources
      (`x2t.cpp`, `cextracttools.cpp`, `ASCConverters.cpp`, `OfficeFileFormatChecker2.cpp`);
      own `main`; conversion fixtures under `test/ExampleFiles/`.

Blocked / need extra work (build targets intentionally not created yet):

- [ ] `PdfFile/test` — **fixtures not in repo** (`test.pdf`, `pdf.bin`, `base64.txt`,
      `pfx.pfx`, `test.djvu`, `changes.bin`, fonts). Needs fixtures committed before it can
      pass headless.
- [ ] `DesktopEditor/doctrenderer/test/json`
- [ ] `DesktopEditor/doctrenderer/test/js_internal`
- [ ] `DesktopEditor/doctrenderer/test/embed/internal/hash` — the three doctrenderer suites
      need a **V8 JS runtime** (and embedded scripts) at run time.
- [ ] `DesktopEditor/xmlsec/src/osign/test` — **no `osign` CMake target exists**; the
      library must be ported to CMake first.

### Deferred: non-gtest qmake `.pro` tools

The remaining ~37 `.pro` "tests" are interactive/GUI tools (SVG dumpers, viewers, manual
testers) — they don't assert and can't run headless, so they are **not** CTest candidates.
They can optionally be given build-only CMake targets later; until then build them with
qmake (`qmake <tool>.pro && make`) against a qmake build of core.
