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
    depname = "Apple",
    workdir = Path( sys.argv[2] ).resolve(), # Work dir is intentionally the same as install dir
    installdir = Path( sys.argv[2] ).resolve(),
    forceredo = len(sys.argv) > 3 and sys.argv[3] == "force-redo"
)

def fetch_and_patch():
    nc.create_workdir()

    repos = [
        { "name": "glm", "url": "https://github.com/g-truc/glm.git", "commit": "33b4a621a697a305bc3a7610d290677b96beb181" },
        { "name": "mdds", "url": "https://github.com/kohei-us/mdds.git", "commit": "0783158939c6ce4b0b1b89e345ab983ccb0f0ad0" },
        { "name": "librevenge", "url": "https://github.com/Distrotech/librevenge.git", "commit": "becd044b519ab83893ad6398e3cbb499a7f0aaf4" },
        { "name": "libodfgen", "url": "https://github.com/Distrotech/libodfgen.git", "commit": "8ef8c171ebe3c5daebdce80ee422cf7bb96aa3bc" },
        { "name": "libetonyek", "url": "https://github.com/LibreOffice/libetonyek.git", "commit": "cb396b4a9453a457469b62a740d8fb933c9442c3" },
    ]
    for repo in repos:
        nc.shallow_checkout( nc.work_dir / repo[ "name" ], repo[ "url" ], repo[ "commit" ] )

    nc.run_command(
        [ "git", "apply", patches_dir / "mdds.patch" ],
        "Patching mdds",
        nc.work_dir / "mdds"
    )

    nc.run_command(
        [ "git", "apply", patches_dir / "librevenge.patch" ],
        "Patching librevenge",
        nc.work_dir / "librevenge"
    )

    nc.run_command(
        [ "git", "apply", patches_dir / "libetonyek.patch" ],
        "Patching libetonyek",
        nc.work_dir / "libetonyek"
    )

    nc.create_work_dir_ok_marker()

    print( "Fetch & patch completed" )

if not nc.work_dir_looks_ok():
    fetch_and_patch()
