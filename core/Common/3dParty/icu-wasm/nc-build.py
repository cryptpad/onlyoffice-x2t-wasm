#!/usr/bin/env python3

import sys
import shutil
import os
from pathlib import Path

script_path = Path(sys.argv[0]).resolve()
script_dir = script_path.parent
icu_major = "74"
icu_minor = "2"

third_party_root = ( script_dir / ".." ).resolve()
if str( third_party_root ) not in sys.path:
    sys.path.insert( 0, str( third_party_root ) )
import build_3rdparty_common as nc

nc.init_for_dep(
    depname = "ICU-WASM",
    workdir = Path( sys.argv[2] ).resolve(), # Work dir is intentionally the same as install dir
    installdir = Path( sys.argv[2] ).resolve(),
    forceredo = len(sys.argv) > 3 and sys.argv[3] == "force-redo"
)

patches_dir = script_dir.parent.parent.parent / "DesktopEditor" / "graphics" / "pro" / "js" / "wasm" / "patches"
# DesktopEditor/graphics/pro/js/wasm/patches/fix-wasm-icu.patch

def fetch_and_patch():
    nc.create_workdir()
    
    nc.run_command(
        [ "git", "-c", "core.autocrlf=false", "-c", "core.eol=lf", "clone",
          "--depth", "1", "--branch", f"release-{icu_major}-{icu_minor}",
          "https://github.com/unicode-org/icu.git", str(nc.work_dir / "icu2")
        ],
        "Checkout git repo",
    )

    try:
        shutil.copytree(
            nc.work_dir / "icu2" / "icu4c",
            nc.work_dir / "icu",
            copy_function=shutil.copy2
        )
    except Exception as e:
        nc.abort_op( f"Copy failed: {e}" )

    try:
        shutil.copy2( nc.work_dir / "icu2" / "LICENSE", nc.work_dir / "LICENSE" )
    except Exception as e:
        nc.abort_op( f"License copy failed: {e}" )

    try:
        shutil.rmtree( nc.work_dir / "icu2" )
    except FileNotFoundError:
        pass

    nc.run_command(
        [ "git", "apply", patches_dir / "fix-wasm-icu.patch" ],
        "Patch ICU-WASM",
        nc.work_dir / "icu"
    )

    nc.create_work_dir_ok_marker()

    print( "Fetch & patch completed" )

if not nc.work_dir_looks_ok():
    fetch_and_patch()

