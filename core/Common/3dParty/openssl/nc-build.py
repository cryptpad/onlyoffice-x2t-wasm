#!/usr/bin/env python3

import sys
import shutil
import os
from pathlib import Path

script_path = Path(sys.argv[0]).resolve()
script_dir = script_path.parent

third_party_root = ( script_dir / ".." ).resolve()
if str( third_party_root ) not in sys.path:
    sys.path.insert( 0, str( third_party_root ) )
import build_3rdparty_common as nc

nc.init_for_dep(
    depname = "OpenSSL",
    workdir = Path( sys.argv[1] ).resolve(),
    installdir = Path( sys.argv[2] ).resolve(),
    forceredo = len(sys.argv) > 3 and sys.argv[3] == "force-redo"
)

def fetch_and_patch():
    nc.create_workdir()

    nc.run_command(
        [   "git", "-c", "core.autocrlf=false", "-c", "core.eol=lf",
            "clone", "--depth", "1",
            "--branch", "OpenSSL_1_1_1f",
            "https://github.com/openssl/openssl.git",
            str(nc.work_dir)
        ],
        "Clone repo"
    )
    
    nc.create_work_dir_ok_marker()

    print( "Fetch & patch completed" )

def build_and_install():
    nc.create_install_dir()
    
    if nc.is_linux():
        nc.run_command(
            [   "./config",
                f"--prefix={nc.install_dir}",
                f"--openssldir={nc.install_dir}",
                "enable-md2",
                "no-shared",
                "no-asm",
            ],
            "Configure",
            nc.work_dir
        )

        nc.run_command(
            [ "make", f"-j{os.cpu_count()}" ],
            "Build",
            nc.work_dir
        )

        nc.run_command(
            [ "make", "install" ],
            "Install",
            nc.work_dir
        )

    elif nc.is_windows():
        
        nc.run_command(
            [   shutil.which("perl"),
                "Configure",
                "VC-WIN64A",
                f"--prefix={nc.install_dir}",
                f"--openssldir={nc.install_dir}",
                "enable-md2",
                "no-shared",
                "no-asm",
            ],
            "Configure",
            nc.work_dir
        )

        nc.run_command(
            [ "nmake" ],
            "Build",
            nc.work_dir
        )

        nc.run_command(
            [ "nmake", "install" ],
            "Install",
            nc.work_dir
        )

    else:
        abort_op( f"Unkown target platform: {sys.platform}" )

    nc.create_install_dir_ok_marker()
    
    print( "Build and install completed" )

def build_all():
    if not nc.work_dir_looks_ok():
        fetch_and_patch()

    if not nc.install_dir_looks_ok():
        if nc.is_windows() and shutil.which("nmake") is None:
            raise RuntimeError(
                "MSVC environment is not set up: 'nmake' not found in PATH.\n"
                "Run 'vcvarsx86_amd64.bat' or use 'x64 Native Tools Command Prompt'."
            )
        build_and_install()
    
nc.ensure_dep( build_all )
