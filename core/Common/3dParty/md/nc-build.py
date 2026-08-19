#!/usr/bin/env python3

import sys
import shutil
from pathlib import Path

script_path = Path(sys.argv[0]).resolve()
script_dir = script_path.parent

third_party_root = ( script_dir / ".." ).resolve()
if str( third_party_root ) not in sys.path:
    sys.path.insert( 0, str( third_party_root ) )
import build_3rdparty_common as nc

nc.init_for_dep(
    depname = "MD",
    workdir = Path( sys.argv[2] ).resolve(), # Work dir is intentionally the same as install dir
    installdir = Path( sys.argv[2] ).resolve(),
    forceredo = len(sys.argv) > 3 and sys.argv[3] == "force-redo"
)

def fetch_and_patch():
    nc.create_workdir()

    nc.run_command(
        [ "git", "clone", "https://github.com/mity/md4c.git", nc.work_dir ],
        "Git clone",
    )

    nc.run_command(
        [ "git", "checkout", "481fbfbdf72daab2912380d62bb5f2187d438408" ],
        "Checkout commit",
        nc.work_dir
    )

    nc.create_work_dir_ok_marker()

    print( "Fetch & patch completed" )

if not nc.work_dir_looks_ok():
    fetch_and_patch()
