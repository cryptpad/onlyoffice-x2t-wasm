#!/usr/bin/env python3

# import os
import sys
import subprocess
import shutil
from pathlib import Path

import build_3rdparty_common as nc

sys.stdout.reconfigure(encoding='utf-8', line_buffering=True)
sys.stderr.reconfigure(encoding='utf-8', line_buffering=True)

subfolders = [
    'apple',
    'boost',
    'brotli',
    'harfbuzz',
    'html',
    'hyphen',
    'icu',
    'icu-wasm',
    'md',
    'openssl',
    'openssl-hash',
    'socketio',
    'hunspell',
    'v8',
]

force_redo_subfolders = []
only_subfolders = []
except_subfolders = []

script_path = Path(sys.argv[0]).resolve()
script_dir = script_path.parent

def print_help():
    print(
        f"""
Usage: { script_path.name } [options] work_dir_abs install_dir_abs
    work_dir_abs    : Absolute path to the work directory (repos will be checked out and built here).
    install_dir_abs : Absolute path to the install directory (artifacts will be installed here).

    Options:
        --list        : Prints a list of known subfolders.
        --force-redo= : A list of subdirectories to re-do even if they are already done.
        --only=       : Build only the specified comma-separated subfolders (skip all others).
        --except=     : Build everything except the specified comma-separated subfolders.
                        Note: --only= and --except= are mutually exclusive.
        --help | -h   : Prints this help.

    Examples:
        { script_path.name } $PWD/work $PWD/install
        Build and install everything to these directories.

        { script_path.name } --force-redo=v8,icu $PWD/work $PWD/install
        Build and install everything to these directories but delete and re-do v8 and icu.

        { script_path.name } --only=v8,icu $PWD/work $PWD/install
        Build and install only v8 and icu.

        { script_path.name } --except=v8,icu $PWD/work $PWD/install
        Build and install everything except v8 and icu.
        """
    )

argc = len( sys.argv )

if ( argc < 2 ):
    print_help()
    sys.exit( 0 )

last_consumed_arg_idx = 0
for i in range( 1, argc ):
    if sys.argv[ i ].startswith( "--force-redo=" ):
        force_redo_subfolders = ( sys.argv[ i ][ len( "--force-redo=" ): ] ).split( ',' )
        for fr_subfolder in force_redo_subfolders:
            if fr_subfolder not in subfolders:
                print( f"Unkown subfolder: { fr_subfolder }" )
                print_help()
                sys.exit( 1 )

    elif sys.argv[ i ].startswith( "--only=" ):
        only_subfolders = ( sys.argv[ i ][ len( "--only=" ): ] ).split( ',' )
        for only_subfolder in only_subfolders:
            if only_subfolder not in subfolders:
                print( f"Unknown subfolder: { only_subfolder }" )
                print_help()
                sys.exit( 1 )

    elif sys.argv[ i ].startswith( "--except=" ):
        except_subfolders = ( sys.argv[ i ][ len( "--except=" ): ] ).split( ',' )
        for ex_subfolder in except_subfolders:
            if ex_subfolder not in subfolders:
                print( f"Unknown subfolder: { ex_subfolder }" )
                print_help()
                sys.exit( 1 )

    elif sys.argv[ i ] == "--list":
        for subfolder in subfolders:
            print( subfolder )
        sys.exit( 0 )

    elif sys.argv[ i ] in [ "--help", "-h" ]:
        print_help()
        sys.exit( 0 )

    elif sys.argv[ i ].startswith( "-" ):
        print( f"Unkown option { sys.argv[ i ] }" )
        sys.exit( 1 )
    
    else:
        break

    last_consumed_arg_idx = i

if last_consumed_arg_idx >= argc - 2:
    print( "Needs at least 2 arguments: work_dir_abs install_dir_abs" )
    print_help()
    sys.exit( 1 )



work_dir = Path( sys.argv[ argc - 2 ] ).resolve()
install_dir = Path( sys.argv[ argc - 1 ] ).resolve()

if sys.platform == "win32" and shutil.which( "nmake" ) is None:
    raise RuntimeError(
        "MSVC environment is not set up: 'nmake' not found in PATH.\n"
        "Run 'vcvars64.bat' or use 'x64 Native Tools Command Prompt'."
    )



if only_subfolders and except_subfolders:
    print( "Error: --only= and --except= are mutually exclusive." )
    sys.exit( 1 )

if only_subfolders:
    subfolders = [ s for s in subfolders if s in only_subfolders ]
elif except_subfolders:
    subfolders = [ s for s in subfolders if s not in except_subfolders ]

total_time = nc.MeasurementObj( "Total" )

for subfolder in subfolders:
    force_redo = subfolder in force_redo_subfolders
    print(  "---------------------------------------------------------------------------" )
    print( f"Working on {subfolder}{ ' (redo forced)' if force_redo else '' }..." )
    sub_script = Path( script_dir / subfolder / "nc-build.py" )
    if sub_script.exists():
        try:
            time_meas = nc.MeasurementObj( subfolder )

            subprocess.run(
                [sys.executable, sub_script, work_dir / subfolder, install_dir / subfolder, "force-redo" if force_redo else "" ],
                check=True,
                text=True,
                stdout=None,
                stderr=None,
            )
            
        except subprocess.CalledProcessError as e:
            print( f"  ❌ {subfolder} failed with code {e.returncode}" )
            print( f"  { time_meas.elapsed_string() }" )
            time_meas.report()
            sys.exit(e.returncode)

        print( f"  ✅ {subfolder} ready" )
        print( f"  { time_meas.elapsed_string() }" )

    else:
        print( f"❌ { subfolder } build script cannot be found ({ sub_script })" )

print( "" )
print( "🎉 Success! 🎉" )
total_time.report()
