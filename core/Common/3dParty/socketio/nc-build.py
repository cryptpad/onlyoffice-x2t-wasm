#!/usr/bin/env python3

import sys
import shutil
from pathlib import Path

script_path = Path(sys.argv[0]).resolve()
script_dir = script_path.parent
patches_dir = script_dir / "patches" / "proper_patches"

third_party_root = ( script_dir / ".." ).resolve()
if str( third_party_root ) not in sys.path:
    sys.path.insert( 0, str( third_party_root ) )
import build_3rdparty_common as nc

nc.init_for_dep(
    depname = "SocketIO",
    workdir = Path( sys.argv[2] ).resolve(), # Work dir is intentionally the same as install dir
    installdir = Path( sys.argv[2] ).resolve(),
    forceredo = len(sys.argv) > 3 and sys.argv[3] == "force-redo"
)

def fetch_and_patch():
    nc.create_workdir()

    nc.shallow_checkout( nc.work_dir, "https://github.com/socketio/socket.io-client-cpp.git", "da779141a7379cc30c870d48295033bc16a23c66" )

    nc.run_command(
        [ "git", "submodule", "update", "--init", "--recursive" ],
        "Init submodules",
        nc.work_dir
    )

    nc.run_command(
        [ "git", "checkout", "230c0d2ae035c5ce1292233fcab03cea0d341264" ],
        "Checkout ASIO",
        nc.work_dir / "lib" / "asio"
    )

    nc.run_command(
        [ "git", "checkout", "56123c87598f8b1dd471be83ca841ceae07f95ba" ],
        "Checkout WebSocketPP",
        nc.work_dir / "lib" / "websocketpp"
    )

    nc.run_command(
        [ "git", "apply", patches_dir / "websocketpp.patch" ],
        "Patch WebSocketPP",
        nc.work_dir / "lib" / "websocketpp"
    )

    patch_cmds = [
        [ "git", "apply", patches_dir / "sio_client_impl_fail.patch" ],
        [ "git", "apply", patches_dir / "sio_client_impl_open.patch" ],
        [ "git", "apply", patches_dir / "sio_client_impl_close_timeout.patch" ],
    ]
    for i, patch_cmd in enumerate( patch_cmds ):
        nc.run_command(
            patch_cmd,
            f"Internals patch {i+1}",
            nc.work_dir / "src" / "internal"
        )
    
    # Create no_tls version
    try:
        shutil.copytree( nc.work_dir / "src", nc.work_dir / "src_no_tls" )
    except Exception as e:
        nc.abort_op( f"No TLS copy failed: {e.stderr.strip() or e.stdout.strip() or e}" )

    nc.run_command(
        [ "git", "apply", patches_dir / "no_tls.patch" ],
        "Patch no TLS version",
        nc.work_dir
    )

    nc.create_work_dir_ok_marker()

    print( "Fetch & patch completed" )

if not nc.work_dir_looks_ok():
    fetch_and_patch()
