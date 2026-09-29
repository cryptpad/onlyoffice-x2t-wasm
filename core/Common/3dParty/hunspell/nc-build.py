#!/usr/bin/env python3

import sys
import shutil
from pathlib import Path

script_path = Path(sys.argv[0]).resolve()
script_dir = script_path.parent
patches_dir = script_dir / "patches"

third_party_root = ( script_dir / ".." ).resolve()
if str( third_party_root ) not in sys.path:
    sys.path.insert( 0, str( third_party_root ) )
import build_3rdparty_common as nc

nc.init_for_dep(
    depname = "Hunspell",
    workdir = Path( sys.argv[2] ).resolve(), # Work dir is intentionally the same as install dir
    installdir = Path( sys.argv[2] ).resolve(),
    forceredo = len(sys.argv) > 3 and sys.argv[3] == "force-redo"
)

def fetch_and_patch():
    nc.create_workdir()

    nc.run_command(
        [   "git", "clone", "--depth", "1", "--branch", "v1.7.2",
            "https://github.com/hunspell/hunspell.git", nc.work_dir / "hunspell"
        ],
        "Clone hunspell"
    )

    # Create wasm version
    try:
        shutil.copytree( nc.work_dir / "hunspell", nc.work_dir / "hunspell-wasm" )
    except Exception as e:
        nc.abort_op( f"Hunspell-wasm copy failed: {e.stderr.strip() or e.stdout.strip() or e}" )

    nc.run_command(
        [ "git", "apply", patches_dir / "fix-wasm-hunspell.patch" ],
        "Patch hunspell-wasm",
        nc.work_dir / "hunspell-wasm"
    )

    nc.create_work_dir_ok_marker()

    print( "Fetch & patch completed" )

if not nc.work_dir_looks_ok():
    fetch_and_patch()
