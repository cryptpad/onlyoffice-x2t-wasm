#!/usr/bin/env python3

import sys
import shutil
from pathlib import Path

script_path = Path(sys.argv[0]).resolve()
script_dir = script_path.parent
patches_dir = script_dir

third_party_root = ( script_dir / ".." ).resolve()
if str( third_party_root ) not in sys.path:
    sys.path.insert( 0, str( third_party_root ) )
import build_3rdparty_common as nc

nc.init_for_dep(
    depname = "HTML",
    workdir = Path( sys.argv[2] ).resolve(), # Work dir is intentionally the same as install dir
    installdir = Path( sys.argv[2] ).resolve(),
    forceredo = len(sys.argv) > 3 and sys.argv[3] == "force-redo"
)

def fetch_and_patch():
    nc.create_workdir()

    nc.shallow_checkout( nc.work_dir / "katana-parser", "https://github.com/jasenhuang/katana-parser.git", "be6df458d4540eee375c513958dcb862a391cdd1" )
    nc.shallow_checkout( nc.work_dir / "gumbo-parser", "https://github.com/google/gumbo-parser.git", "aa91b27b02c0c80c482e24348a457ed7c3c088e0" )

    nc.run_command(
        [ "git", "apply", patches_dir / "katana.patch" ],
        "Patch katana-parser",
        nc.work_dir / "katana-parser"
    )

    nc.run_command(
        [ "git", "apply", patches_dir / "gumbo.patch" ],
        "Patch gumbo-parser",
        nc.work_dir / "gumbo-parser"
    )

    nc.create_work_dir_ok_marker()

    print( "Fetch & patch completed" )

if not nc.work_dir_looks_ok():
    fetch_and_patch()
