import sys
import shutil
import stat
import subprocess
import os
import time
import platform
import tempfile
from pathlib import Path

_original_rmtree = shutil.rmtree

def _force_remove(func, path, exc):
    try:
        os.chmod(path, stat.S_IWRITE)
    except OSError:
        pass
    for _ in range(5):
        try:
            func(path)
            return
        except PermissionError:
            time.sleep(0.5)
    func(path)  # final attempt; raises if genuinely locked

def _safe_rmtree(path, *args, **kwargs):
    if sys.version_info >= (3, 12):
        kwargs.setdefault("onexc", _force_remove)
    else:
        kwargs.setdefault("onerror", _force_remove)
    return _original_rmtree(path, *args, **kwargs)

shutil.rmtree = _safe_rmtree
# --- end read-only-safe rmtree ---

dep_name = None
debug_mode = False
work_dir = None
install_dir = None
force_redo = False

def init_for_dep(
    depname : str,
    workdir : Path,
    installdir : Path,
    forceredo : bool,
    debugmode : bool = True
):
    global dep_name, work_dir, install_dir, force_redo, debug_mode, log_cleared

    dep_name = depname
    work_dir = workdir
    install_dir = installdir
    force_redo = forceredo
    debug_mode = debugmode
    log_cleared = False
    
def abort_op( message : str, keep_work : bool = False, error_is_fatal : bool = True ):
    print( f"Aborting {dep_name}: {message}", file = sys.stderr )
    if error_is_fatal:
        if not debug_mode:
            try:
                if not keep_work:
                    shutil.rmtree( work_dir )
                shutil.rmtree( install_dir )
            except FileNotFoundError:
                pass
        sys.exit( 1 )

def is_linux() -> bool:
    return sys.platform.startswith("linux")

def is_windows() -> bool:
    return sys.platform == "win32"

def work_dir_looks_ok() -> bool:
    return ( not force_redo ) and Path( work_dir / "ok_marker" ).exists()

def install_dir_looks_ok() -> bool:
    return ( not force_redo ) and Path( install_dir / "ok_marker" ).exists()

def create_work_dir_ok_marker():
    Path( work_dir / "ok_marker" ).touch()

def create_install_dir_ok_marker():
    Path( install_dir / "ok_marker" ).touch()

def create_workdir():
    # If exists and needed, remove work dir
    if work_dir.exists() and ( force_redo or not work_dir_looks_ok() ):
        try:
            shutil.rmtree( work_dir )
        except FileNotFoundError:
            pass

    # Create work dir (if needed)
    if not work_dir.exists():
        try:
            work_dir.mkdir( parents = True )
        except OSError:
            abort_op( "Failed to create work dir" )

def create_install_dir():
    # If exists and needed, remove install dir
    if install_dir.exists() and ( force_redo or not install_dir_looks_ok() ):
        try:
            shutil.rmtree( install_dir )
        except FileNotFoundError:
            pass

    # Create install dir (if needed)
    if not install_dir.exists():
        try:
            install_dir.mkdir( parents = True )
        except OSError:
            abort_op( "Failed to create install dir" )

def ensure_directory_exists( dir : Path ):
    if not dir.exists():
        dir.mkdir( parents = True )

def run_command(
        cmd : list[str],
        description : str, cwd : Path | None = None,
        verbose : bool = False,
        error_is_fatal : bool = True,
        env : dict[ str, str ] | None = None
    ):

    cwd = (cwd or Path.cwd()).resolve()
    output_pipe = None if verbose else subprocess.PIPE
    final_env = os.environ.copy() | ( {} if env is None else env )

    try:
        _ = subprocess.run( cmd, check=True, stdout=output_pipe, stderr=output_pipe, text=True, cwd=cwd, env = final_env )
    except subprocess.CalledProcessError as e:
        if verbose:
            abort_op( f"{description} failed", error_is_fatal=error_is_fatal )
        else:
            abort_op( f"{description} failed: {e.stderr.strip() or e.stdout.strip() or e}", error_is_fatal=error_is_fatal )

def capture_process_output( cmd : list[str] ) -> str:
    result = subprocess.run( cmd, capture_output = True, text = True, check = True )
    return result.stdout

def fix_terminal_encoding():
    sys.stdout.reconfigure( encoding='utf-8' )
    if is_windows():
        os.system( 'chcp 65001 >nul' )

def shallow_checkout( repo_dir : Path, repo_url : str, commit : str ):
    if repo_dir.exists():
        def onerror(func, path, exc_info):
            os.chmod(path, stat.S_IWRITE)
            func(path)
        try:
            if sys.version_info >= (3, 12):
                shutil.rmtree( repo_dir, onexc=onerror )
            else:
                shutil.rmtree( repo_dir, onerror=onerror )
        except FileNotFoundError:
            pass

    # Create work dir (if needed)
    if not repo_dir.exists():
        try:
            repo_dir.mkdir( parents = True )
        except OSError:
            abort_op( "Failed to create repo dir" )

    run_command(
        [ "git", "init" ],
        f"Git init ({repo_dir.name})",
        repo_dir
    )

    run_command(
        [ "git", "remote", "add", "origin", repo_url ],
        f"Add origin ({repo_dir.name})",
        repo_dir
    )

    run_command(
        [ "git", "fetch", "--depth", "1", "origin", commit ],
        f"Fetch commit ({repo_dir.name})",
        repo_dir
    )

    run_command(
        [ "git", "checkout", "FETCH_HEAD" ],
        f"Checkout head ({repo_dir.name})",
        repo_dir
    )

class MeasurementObj:
    def __init__( self, name: str ):
        self.name = name
        self.start = time.perf_counter()

    def report( self ):
        end = time.perf_counter()
        elapsed = end - self.start
        print( f"{self.name}: {elapsed:.6f} second(s)" )
        
    def elapsed_string( self ) -> float:
        end = time.perf_counter()
        elapsed = end - self.start
        return f"{elapsed:.6f} second(s)"


# ===========================================================================
# Remote cache (Nextcloud WebDAV)
#
# One entry point: ensure_dep(build_fn). Call it from every nc-build.py instead
# of the manual `if not install_dir_looks_ok(): build_fn()` check. It will:
#   0. skip if the install dir already looks ok locally
#   1. else download + extract a prebuilt archive from the remote, if present
#   2. else run build_fn() (which must end by creating the ok-marker) and then
#      archive the install dir and upload it for next time
#
# It relies on the module state that init_for_dep() already sets:
#   - install_dir              (the resolved install dir; confirmed used elsewhere)
#   - install_dir_looks_ok()   (the ok-marker check)
#   - the force-redo flag       (read defensively below)
#
# Credentials come from the environment so nothing is committed:
#   NEXTCLOUD_USER, NEXTCLOUD_PASS.   'curl' must be on PATH when they are set.
# If either is empty the remote cache is disabled and ensure_dep behaves like
# the old manual check (build locally only).
# ===========================================================================

NEXTCLOUD_USER   = os.environ.get( "NEXTCLOUD_USER", "" )
NEXTCLOUD_PASS   = os.environ.get( "NEXTCLOUD_PASS", "" )
NEXTCLOUD_REMOTE = "https://cloud.nextcloud.com/remote.php/dav/files"
BASE_REMOTE_PATH = "3DPARTY_DEPS_1"
# Keep OS/arch builds apart on the remote, e.g. "linux-x86_64", "win32-AMD64".
PLATFORM_TAG     = f"{ sys.platform }-{ platform.machine() }"
USE_REMOTE_CACHE = bool( NEXTCLOUD_USER and NEXTCLOUD_PASS )


def _force_redo_flag():
    # init_for_dep() stores the forceredo flag in a module global; accept a few
    # likely names so this works without knowing the exact one.
    g = globals()
    for nm in ( "force_redo", "forceredo", "_force_redo" ):
        if nm in g:
            return bool( g[ nm ] )
    return False


def _cache_key():
    # Folder name of the install dir, e.g. "harfbuzz". Stable across runs and
    # independent of the (sometimes capitalised) depname.
    return install_dir.name


def _remote_file_url():
    key = _cache_key()
    return ( f"{ NEXTCLOUD_REMOTE }/{ NEXTCLOUD_USER }/{ BASE_REMOTE_PATH }"
             f"/{ PLATFORM_TAG }/{ key }/{ key }.tar.bz2" )


def _curl( *args ):
    return subprocess.run(
        [ "curl", "-s", "-u", f"{ NEXTCLOUD_USER }:{ NEXTCLOUD_PASS }", *args ],
        text=True, capture_output=True,
    )


def _remote_exists():
    # HEAD request: True only on a 2xx status code.
    r = _curl( "-o", os.devnull, "-w", "%{http_code}", "--head", _remote_file_url() )
    return r.stdout.strip().startswith( "2" )


def _remote_download_and_extract():
    with tempfile.TemporaryDirectory() as tmp:
        archive = str( Path( tmp ) / "dep.tar.bz2" )
        if _curl( "-f", "-o", archive, _remote_file_url() ).returncode != 0:
            return False
        if install_dir.exists():
            shutil.rmtree( install_dir )
        install_dir.mkdir( parents=True, exist_ok=True )
        shutil.unpack_archive( archive, str( install_dir ) )
        return True


def _remote_upload():
    with tempfile.TemporaryDirectory() as tmp:
        # Archive into a temp dir so the .tar.bz2 is never inside install_dir
        # (important since work dir and install dir can be the same path).
        archive = shutil.make_archive( str( Path( tmp ) / _cache_key() ),
                                       "bztar", root_dir=str( install_dir ) )
        base = f"{ NEXTCLOUD_REMOTE }/{ NEXTCLOUD_USER }"
        key  = _cache_key()
        # WebDAV does not create intermediate collections, so MKCOL each level
        # (MKCOL on an existing collection just 405s, which we ignore).
        for part in ( BASE_REMOTE_PATH,
                      f"{ BASE_REMOTE_PATH }/{ PLATFORM_TAG }",
                      f"{ BASE_REMOTE_PATH }/{ PLATFORM_TAG }/{ key }" ):
            _curl( "-X", "MKCOL", f"{ base }/{ part }" )
        _curl( "-X", "DELETE", _remote_file_url() )
        return _curl( "-f", "-T", archive, _remote_file_url() ).returncode == 0


def ensure_dep( build_fn, forceredo=None ):
    """
    Drop-in replacement for `if not install_dir_looks_ok(): build_fn()`.

    Call once per dependency, after init_for_dep(). `build_fn` must create the
    ok-marker (e.g. via create_install_dir_ok_marker()) when it finishes -- the
    marker is what makes the dep count as "done" both locally and inside the
    uploaded archive.
    """
    force_redo = _force_redo_flag() if forceredo is None else bool( forceredo )
    name = _cache_key()

    # 0. Already built locally. install_dir_looks_ok() already returns False on
    #    a forced redo, so this correctly does NOT skip in that case.
    if install_dir_looks_ok():
        print( f"  \u2705 { name } already present locally, skipping" )
        return

    # 1. Prebuilt archive on the remote (skipped on a forced redo so we rebuild
    #    and refresh the remote instead of pulling a stale copy).
    if USE_REMOTE_CACHE and not force_redo and _remote_exists():
        print( f"  \u2b07\ufe0f  Found { name } on remote, downloading..." )
        if _remote_download_and_extract() and install_dir_looks_ok():
            print( f"  \u2705 { name } fetched from remote" )
            return
        print( "  \u26a0\ufe0f  Remote copy missing/incomplete, building locally." )

    # 2. Build locally, then archive + upload for next time.
    build_fn()
    if not install_dir_looks_ok():
        print( f"  \u26a0\ufe0f  { name }: build finished but no ok-marker was created" )
        return
    if USE_REMOTE_CACHE:
        print( f"  \u2b06\ufe0f  Uploading { name } to remote..." )
        if _remote_upload():
            print( f"  \u2705 { name } uploaded" )
        else:
            print( f"  \u26a0\ufe0f  Upload of { name } failed" )