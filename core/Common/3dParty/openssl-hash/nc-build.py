#!/usr/bin/env python3

import sys
import shutil
import os
import re
from pathlib import Path

script_path = Path(sys.argv[0]).resolve()
script_dir = script_path.parent

third_party_root = ( script_dir / ".." ).resolve()
if str( third_party_root ) not in sys.path:
    sys.path.insert( 0, str( third_party_root ) )
import build_3rdparty_common as nc

patches_dir_1 = script_dir.parent.parent.parent / "DesktopEditor" / "xmlsec" / "src" / "wasm" / "3rdParty" / "patches"
patches_dir_2 = script_dir.parent.parent.parent / "DesktopEditor" / "graphics" / "pro" / "js" / "wasm" / "patches"

nc.init_for_dep(
    depname = "OpenSSL-HASH",
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

    nc.run_command(
        [ "git", "apply", patches_dir_1 / "fix-wasm-openssl.patch" ],
        "Patch OpenSSL-HASH #1",
        nc.work_dir
    )

    nc.run_command(
        [ "git", "apply", patches_dir_2 / "fix-wasm-openssl.patch" ],
        "Patch OpenSSL-HASH #2",
        nc.work_dir
    )
    
    nc.create_work_dir_ok_marker()

    print( "Fetch & patch completed" )

def build_and_install():
    nc.create_install_dir()

    if shutil.which( "emmake" ) is None:
        nc.abort_op( "Tool not found: emmake - Emsdk is probably not activated" )
    
    if nc.is_linux():
        # Set compiler flags to handle OpenSSL 1.1.1f compatibility with newer Emscripten
        env = os.environ.copy()
        env["CFLAGS"] = "-Wno-implicit-int -Wno-error=implicit-int -Wno-deprecated-declarations"
        env["CXXFLAGS"] = "-Wno-implicit-int -Wno-error=implicit-int -Wno-deprecated-declarations"

        nc.run_command(
            [   "emconfigure",
                "./config",
                "no-shared",
                "no-asm",
                "no-threads",
                "no-dso",
                "no-deprecated",
                "enable-md2",
                f"--prefix={nc.install_dir}",
                f"--openssldir={nc.install_dir}",
            ],
            "Configure",
            nc.work_dir,
            env = env
        )

        # Fiddle with the makefile
        try:
            path = nc.work_dir / "Makefile"
            content = path.read_text()
            content = re.sub(
                r"^CROSS_COMPILE.*$",
                "CROSS_COMPILE=",
                content,
                flags=re.MULTILINE,
            )
            path.write_text(content)
        except Exception as e:
            nc.abort_op( "Failed to fix Makefile" )

        nc.run_command(
            [   "emmake",
                "make",
                f"-j{os.cpu_count()}",
                "build_generated",
                "libcrypto.a",
                "libssl.a",
            ],
            "Build",
            nc.work_dir,
            env = env
        )

        nc.run_command(
            [ "make", "install" ],
            "Install",
            nc.work_dir
        )

    else:
        nc.abort_op( f"Unkown target platform: {sys.platform}" )

    nc.create_install_dir_ok_marker()
    
    print( "Build and install completed" )

if nc.is_windows():
    print( "WARNING: OpenSSL Wasm build is not implemented on Windows - skipping" )
    sys.exit( 0 )

if not nc.work_dir_looks_ok():
    fetch_and_patch()

def build_all():

    if not nc.install_dir_looks_ok():
        build_and_install()

nc.ensure_dep( build_all )