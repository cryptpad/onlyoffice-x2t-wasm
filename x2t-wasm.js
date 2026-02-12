const process = require('node:process');
const x2t = require('./x2t');

function copyToWasm(nodePath, wasmPath) {
  const data = fs.readFileSync(nodePath);
  const stream = x2t.FS.open(wasmPath, 'w');
  x2t.FS.write(stream, data, 0, data.length, 0);
  x2t.FS.close(stream);
}

function copyDirToWasm(nodePath, wasmPath) {
  if (fs.statSync(nodePath).isDirectory()) {
    try {
      x2t.FS.mkdir(wasmPath);
    } catch(e) {}
    const dir = fs.readdirSync(nodePath);
    for (const f of dir) {
      copyDirToWasm(path.join(nodePath, f), path.join(wasmPath, f));
    }
  } else {
    copyToWasm(nodePath, wasmPath);
  }
}

function copyFromWasm(wasmPath, nodePath) {
  const data = x2t.FS.readFile(wasmPath, {encoding: 'binary'});
  fs.writeFileSync(nodePath, data);
}

function initWorkDir() {
  rmr(x2t.FS, '/working');
  rmr(x2t.FS, '/tmp');
  x2t.FS.mkdir('/tmp');
  x2t.FS.mkdir('/working');
  x2t.FS.mkdir('/working/media');
  x2t.FS.mkdir('/working/fonts');
  x2t.FS.mkdir('/working/themes');
  copyDirToWasm('tests/fonts', '/working/fonts');
}

function rmr(FS, p) {
  if (!FS.analyzePath(p).exists) {
    return;
  }

  if (FS.isDir(FS.stat(p).mode)) {
    FS.readdir(p)
      .filter(e => e !== '.' && e !== '..')
      .forEach(e => rmr(FS, path.join(p, e)));
    if (p !== '/') {
      FS.rmdir(p);
    }
  } else {
    FS.unlink(p);
  }
}

x2t.onRuntimeInitialized = function() {
  try {
    testFilesInDir('tests');
    console.log('success');
  } catch(e) {
    console.error(e);
      process.exit(1);
  }
};
