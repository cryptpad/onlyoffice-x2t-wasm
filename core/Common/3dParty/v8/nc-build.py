#!/usr/bin/env python3

import sys
import shutil
import os
import platform
import re
from pathlib import Path

script_path = Path(sys.argv[0]).resolve()
script_dir = script_path.parent

third_party_root = ( script_dir / ".." ).resolve()
if str( third_party_root ) not in sys.path:
    sys.path.insert( 0, str( third_party_root ) )
import build_3rdparty_common as nc

nc.init_for_dep(
    depname = "V8",
    workdir = Path( sys.argv[1] ).resolve(),
    installdir = Path( sys.argv[2] ).resolve(),
    forceredo = len(sys.argv) > 3 and sys.argv[3] == "force-redo"
)

depot_tools_path = nc.work_dir / "depot_tools"
v8_root_path = nc.work_dir / "v8"
v8_src_path = v8_root_path / "v8"

gn_source_path = nc.work_dir / "gn-source"

def check_prequisites():
    tools_needed = [ "git", "python3" ]
    if nc.is_linux():
        tools_needed.append( "clang" )
        tools_needed.append( "ninja" )
    for tool in tools_needed:
        if shutil.which( tool ) is None:
            nc.abort_op( f"Tool not found: {tool}" )

def apply_patches():
    patches_dir = script_dir / "tools" / "8.9" / "x64-linux-dynamic"

    patches = [
        { "name": "gclient_paths.patch", "dir": depot_tools_path },
        { "name": "jinja2.patch", "dir": v8_src_path / "third_party" / "jinja2" },
        { "name": "buildgn.patch", "dir": v8_src_path },
    ]

    for patch in patches:
        if patch[ "dir" ].is_dir():
            nc.run_command(
                [ "git", "apply", patches_dir / patch[ "name" ] ],
                f"Applying patch: { patch[ 'name' ] }",
                patch[ "dir" ]
            )
        else:
            print( f"[WARNING] cannot apply patch ({ patch[ 'name' ] }) because dir doesn't exist!" )

    if nc.is_windows():
        nc.run_command(
                [ "git", "apply", script_dir / "tools" / "8.9" / "x64-windows" / "win_toolchain.patch" ],
                "Applying patch: win_toolchain.patch",
                v8_src_path / "build"
            )

def disable_gmock():
    gmock_gn_file_path = v8_src_path / "testing" / "gmock" / "BUILD.gn"
    content = """
# Copyright 2015 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# Disabled to avoid visibility issues with gtest_config
# V8 monolithic build doesn't need gmock

import("//build_overrides/build.gni")

group("gmock") {
testonly = true
}

group("gmock_main") {
testonly = true
}
"""

    gmock_gn_file_path.write_text( content )

def disable_cppgc():
    cppgc_gn_file_path = v8_src_path / "src" / "heap" / "cppgc" / "BUILD.gn"
    content = """
# Copyright 2020 the V8 project authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# Disabled to avoid ARM64 toolchain issues

import("//build/config/sanitizers/sanitizers.gni")
import("../../gni/v8.gni")

group("cppgc_base") {
  visibility = [ ":*" ]
}

group("cppgc_base_for_testing") {
  testonly = true
  visibility = [ ":*" ]
}
"""

    cppgc_gn_file_path.write_text( content )

def build_gn() -> Path:
    print( "Fetching and building gn" )
    nc.shallow_checkout( gn_source_path, "https://gn.googlesource.com/gn", "281ba2c91861b10fec7407c4b6172ec3d4661243" )

    nc.ensure_directory_exists( gn_source_path / "out" )

    env = {
        "CC": "clang",
        "CXX": "clang++"
    } if nc.is_linux() else {
        "CXXFLAGS": "/FIstring",
        "CFLAGS": "/FIstring",
    }

    nc.run_command(
        [ "python", "build/gen.py", "--no-last-commit-position" ],
        "Generate GN build",
        cwd = gn_source_path,
        env = env
    )

    content = """
#pragma once
#define LAST_COMMIT_POSITION_NUM 0
#define LAST_COMMIT_POSITION "0 (unknown)"
"""
    ( gn_source_path / "out" / "last_commit_position.h" ).write_text( content )

    nc.run_command(
        [ "ninja", "-C", "out" ],
        "Building GN",
        cwd = gn_source_path,
        env = env
    )

    gn_bin_name = "gn.exe" if nc.is_windows() else "gn"
    gn_bin_path = v8_src_path / "buildtools" / "linux64" / "gn-built"

    nc.ensure_directory_exists( gn_bin_path )

    try:
        shutil.copy2( gn_source_path / "out" / gn_bin_name, gn_bin_path )
    except Exception as e:
        nc.abort_op( f"Failed to copy gn binary: {e}" )

    return gn_bin_path / gn_bin_name

def get_cpu() -> str:
    arch = platform.machine().lower()
    if arch in [ "x86_64", "amd64" ]:
        return "x64"
    elif arch in [ "aarch64", "arm64" ]:
        return "arm64"
    else:
        nc.abort_op( f"Unsupported architecture: {arch}" )

def get_gn_args_file_content() -> str:
    targetarch = get_cpu()

    if nc.is_linux():
        clang_path = Path(shutil.which("clang"))
        clang_dir = clang_path.parent.parent
        use_bundled_clang = os.environ.get("V8_USE_BUNDLED_CLANG", "false").lower() == "true"

        gn_args=f"""
target_os="linux"
target_cpu="{targetarch}"
v8_target_cpu="{targetarch}"

is_debug=false
is_component_build=false
is_official_build=false

is_clang=true
clang_use_chrome_plugins=false

use_sysroot=false
use_custom_libcxx=false

# Symbol and debug settings
symbol_level=0
strip_debug_info=true
treat_warnings_as_errors=false

# V8 core settings
v8_monolithic=true
v8_use_external_startup_data=false
v8_enable_i18n_support=false
v8_enable_webassembly=false
v8_enable_pointer_compression=true
v8_enable_sandbox=false

# Disable cppgc to avoid build issues
cppgc_enable_caged_heap=false
v8_enable_conservative_stack_scanning=false
cppgc_is_standalone=false

# Disable all testing infrastructure - CRITICAL for avoiding gmock/gtest issues
v8_enable_test_features=false
v8_enable_verify_heap=false
v8_enable_verify_predictable=false
build_with_chromium=false

# Explicitly disable test targets
v8_enable_backtrace=false
v8_enable_disassembler=false
v8_enable_object_print=false

# Additional stability flags
v8_use_snapshot=true
v8_enable_lazy_source_positions=false
v8_enable_gdbjit=false
v8_enable_vtunejit=false
v8_enable_handle_zapping=false

# Use system toolchain properly
use_gold=false
use_lld=true
"""

        if targetarch == "arm64" or ( not use_bundled_clang ):
            gn_args += f"""
clang_base_path="{clang_dir}"
cc="clang"
cxx="clang++"
"""

        return gn_args
    
    elif nc.is_windows():
        gn_args=f"""
target_os="win"
target_cpu="{targetarch}"
v8_target_cpu="{targetarch}"

is_debug=false
is_component_build=false
is_official_build=false

is_clang=false

use_custom_libcxx=false

# Symbol and debug settings
symbol_level=0
treat_warnings_as_errors=false

# V8 core settings
v8_monolithic=true
v8_use_external_startup_data=false
v8_enable_i18n_support=false
v8_enable_webassembly=false
v8_enable_pointer_compression=true
v8_enable_sandbox=false

# Disable cppgc to avoid build issues
cppgc_enable_caged_heap=false
v8_enable_conservative_stack_scanning=false
cppgc_is_standalone=false

# Disable all testing infrastructure - CRITICAL for avoiding gmock/gtest issues
v8_enable_test_features=false
v8_enable_verify_heap=false
v8_enable_verify_predictable=false
build_with_chromium=false

# Explicitly disable test targets
v8_enable_backtrace=false
v8_enable_disassembler=false
v8_enable_object_print=false

# Additional stability flags
v8_use_snapshot=true
v8_enable_lazy_source_positions=false
v8_enable_gdbjit=false
v8_enable_vtunejit=false
v8_enable_handle_zapping=false
"""
        return gn_args
    
    else:
        nc.abort_op( "No gn args prepared for os." )
        return "No gn args prepared for os."
    
def create_fake_pipes_shim() -> Path:
    shims_path = nc.work_dir / "win_python_shims"
    shim_file_path = shims_path / "sitecustomize.py"
    nc.ensure_directory_exists( shims_path )
    content = """
import sys
import shlex

# Fake the missing Unix module
class PipesModule:
    @staticmethod
    def quote(s):
        return shlex.quote(s)

sys.modules["pipes"] = PipesModule()
"""
    shim_file_path.write_text( content )
    return shims_path

def fetch_and_patch():
    nc.create_workdir()

    # Get depot_tools
    print( "Fetching depot_tool" )
    nc.run_command(
        [ "git", "clone", "https://chromium.googlesource.com/chromium/tools/depot_tools.git", depot_tools_path ],
        "Clone depot_tools"
    )

    # Update depot_tools
    nc.run_command(
        [ "git", "pull", "origin", "main" ],
        "Update depot_tools",
        depot_tools_path,
        error_is_fatal = False
    )

    # Fetch v8
    print( "Fetching v8" )
    nc.run_command( [ "git", "clone", "https://chromium.googlesource.com/v8/v8.git", v8_src_path ], "Clone v8" )
    nc.run_command( [ "git", "checkout", "8.9.45" ], "Git checkout 8.9.45", v8_src_path )

    nc.create_work_dir_ok_marker()

    print( "Fetch & patch completed" )

def build_and_install():
    nc.create_install_dir()

    # Clean gclient state
    files_to_remove = [ ".gclient", ".gclient_entries", "_bad_scm", "chromium.googlesource.com" ]
    for file in files_to_remove:
        Path( v8_root_path / file ).unlink( missing_ok = True )

    # Clean v8 state
    nc.run_command( [ "git", "reset", "--hard" ], "Git reset", v8_src_path )
    nc.run_command( [ "git", "clean", "-fdx" ], "Git clean", v8_src_path )
    nc.run_command( [ "git", "fetch", "origin" ], "Git fetch", v8_src_path )

    # Clean jinja state
    if ( v8_src_path / "third_party" / "jinja2" ).is_dir():
        nc.run_command( [ "git", "reset", "--hard" ], "Git reset (jinja)", v8_src_path / "third_party" / "jinja2" )
        nc.run_command( [ "git", "clean", "-fd" ], "Git clean (jinja)", v8_src_path / "third_party" / "jinja2" )

    # Clean depot tools
    nc.run_command( [ "git", "reset", "--hard" ], "Git reset (depot_tools)", depot_tools_path )
    nc.run_command( [ "git", "clean", "-fd" ], "Git clean (depot_tools)", depot_tools_path )

    # Create gclient config
    content = """
solutions = [
    {
        "name": "v8",
        "url": "https://chromium.googlesource.com/v8/v8.git",
        "deps_file": "DEPS",
        "managed": False,
        "custom_deps": {},
    },
]
    """
    Path( v8_root_path / ".gclient" ).write_text(content)

    # Sync v8 dependencies
    print( "Synching v8 dependencies" )
    depot_env = os.environ.copy()
    depot_env["PATH"] = f"{depot_tools_path}{os.pathsep}" + depot_env["PATH"]
    depot_env["GCLIENT_SUPPRESS_GIT_VERSION_WARNING"] = "1"
    depot_env["GYP_CHROMIUM_NO_ACTION"] = "1"
    depot_env["DEPOT_TOOLS_WIN_TOOLCHAIN"] = "0"

    if nc.is_windows():
        fake_pipes_shim_path = create_fake_pipes_shim()
        depot_env[ "PYTHONPATH" ] = str( fake_pipes_shim_path )

    
    # Since I'm patching v8/build, I need to reset it before sync (if already exists)
    if ( v8_src_path / "build" ).is_dir():
        nc.run_command(
            [ "git", "reset", "--hard" ],
            "Hard reset v8/build",
            v8_src_path / "build"
        )

    if nc.is_linux() or nc.is_windows():
        if nc.is_linux():
            nc.run_command(
                [ "gclient", "sync", "--no-history", "--shallow" ],
                "GClient sync",
                v8_root_path,
                env = depot_env,
            )
        else: # win
            
            nc.run_command(
                [ "cmd.exe", "/c", "gclient.bat", "sync", "--no-history", "--shallow" ],
                "GClient sync",
                v8_root_path,
                env = depot_env,
            )

        apply_patches()
        disable_gmock()
        disable_cppgc()
        gn_bin_path = build_gn()

        targetarch = get_cpu()
        output_path = v8_src_path / "out.gn"/ f"{targetarch}.release"

        # ensure out dir is clean
        try:
            shutil.rmtree( output_path )
        except FileNotFoundError:
            pass

        gn_args = get_gn_args_file_content()

        if targetarch == "arm64":
            # Check clang version (it must be 13)
            clang_version_output = nc.capture_process_output( [ "clang", "--version" ] )
            match = re.search( r'\d+\.\d+\.\d+', clang_version_output )
            version = match.group() if match else None

            if not version.startswith( "13." ):
                nc.abort_op( f"Need clang 13 in path. Currently it's: { version }" )

        nc.ensure_directory_exists( output_path )
        gn_args_file_path = Path( output_path / "args.gn" )
        gn_args_file_path.write_text( gn_args )

        print( "Running gn gen" )
        gn_rt_env = { "PYTHONPATH": "" }
        if nc.is_windows():
            gn_rt_env[ "PYTHONPATH" ] = str( fake_pipes_shim_path )
            gn_rt_env[ "DEPOT_TOOLS_WIN_TOOLCHAIN" ] = "0"
            gn_rt_env[ "vs2022_install" ] = str( Path( os.environ[ "VSINSTALLDIR" ] ) )
            
        nc.run_command(
            [ gn_bin_path, "gen", output_path ],
            "Running gn",
            v8_src_path,
            env = gn_rt_env
        )

        if not Path( output_path / "build.ninja" ).exists():
            nc.abort_op( "build.ninja not generated!" )

        # Check that the tools actually exist
        for tool in [ "ninja" ]:
            if shutil.which( tool ) is None:
                nc.abort_op( f"Tool not found: {tool}" )

        job_count = max( os.cpu_count() or 1, 4 ) # at least 4 jobs
        if nc.is_windows():
            # On Windows, MSVC is more likely to run out of memory if it uses too many workers. TODO: Maybe we could set an optimal job count based on free memory and cpu core count.
            job_count = 4

        print( "Building v8" )
        env = {
            "CC": "clang",
            "CXX": "clang++"
        } if nc.is_linux() else {
            # "CXXFLAGS": "/FIstring /Zm300",
            # "CFLAGS": "/FIstring /Zm300",
            "CL": "/FIstring /Zm300",
        }
        nc.run_command(
            [ "ninja", "-C", output_path, f"-j{job_count}", "v8_monolith" ],
            "Building v8",
            v8_src_path,
            env=env
        )

        # Verify final artifact
        artifact_name = "v8_monolith.lib" if nc.is_windows() else "libv8_monolith.a"
        if not ( output_path / "obj" / artifact_name ).exists():
            nc.abort_op( f"Build completed but { artifact_name } not found" )

        print( "Installing v8" )
        try:
            shutil.copy2( output_path / "obj" / artifact_name, nc.install_dir / artifact_name )
        except Exception:
            nc.abort_op( f"Failed to install { artifact_name }" )

        nc.ensure_directory_exists( nc.install_dir / "v8" / "include" )
        try:
            shutil.copytree( v8_src_path / "include", nc.install_dir / "v8" / "include", dirs_exist_ok = True )
        except Exception as e:
            nc.abort_op( f"Failed to install public headers ({ e })" )

        src = v8_src_path / "src"
        dst = nc.install_dir / "v8" / "src"
        try:
            for file in src.rglob( "*.h" ):
                relative = file.relative_to( src )
                target = dst / relative
                nc.ensure_directory_exists( target.parent )
                shutil.copy2( file, target )
        except Exception as e:
            nc.abort_op( f"Failed to install private headers ({e})" )

        # Create pkg-config file
        pkg_cfg_file = f"prefix={ nc.install_dir }"
        pkg_cfg_file = pkg_cfg_file + """
libdir=${prefix}
includedir=${prefix}/v8/include

Name: V8
Description: V8 JavaScript Engine
Version: 8.9.45
Libs: -L${libdir} -lv8_monolith -pthread
Cflags: -I${includedir}
"""
        ( nc.install_dir / "v8.pc" ).write_text( pkg_cfg_file )
        
    else:
        nc.abort_op( f"Unkown target platform: {sys.platform}" )

    nc.create_install_dir_ok_marker()
    
    print( "Build and install completed" )

def build_all():
    # Everything required to produce the install dir locally. ensure_dep() only
    # calls this when the install dir is neither present locally nor on the
    # remote, so prerequisites and the large, host-specific work-dir fetch are
    # skipped entirely on a cache hit (a download-only machine needs no compiler).
    check_prequisites()

    if not nc.work_dir_looks_ok():
        fetch_and_patch()

    if nc.is_windows() and shutil.which( "nmake" ) is None:
        raise RuntimeError(
            "MSVC environment is not set up: 'nmake' not found in PATH.\n"
            "Run 'vcvarsx86_amd64.bat' or use 'x64 Native Tools Command Prompt'."
        )

    build_and_install()   # ends by creating the install-dir ok-marker


nc.ensure_dep( build_all )