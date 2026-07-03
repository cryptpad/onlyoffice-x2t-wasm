#!/usr/bin/env node

const fs = require('node:fs');
const path = require('node:path');
const vm = require('node:vm');

const repoRoot = path.resolve(__dirname, '..');
const buildDir = path.resolve(process.argv[2] || path.join(repoRoot, 'build'));
const x2tJs = path.join(buildDir, 'x2t.js');

if (!fs.existsSync(x2tJs)) {
  console.error(`Missing ${x2tJs}. Run: docker build --target output -o build .`);
  process.exit(1);
}

const usingDefaultHtml = !process.env.HTML2MD_HTML;
const html = process.env.HTML2MD_HTML ||
  '<!doctype html><html><head></head><body><p>Hello <a href="https://example.com" title="Example">world</a></p></body></html>';

const context = {
  console,
  process,
  require,
  Buffer,
  Uint8Array,
  ArrayBuffer,
  WebAssembly,
  performance,
  setTimeout,
  clearTimeout,
  __filename: x2tJs,
  __dirname: buildDir,
  module: { exports: {} },
  exports: {},
  crypto: globalThis.crypto || require('node:crypto').webcrypto,
};

context.global = context;
context.globalThis = context;
context.self = context;
context.Module = {
  locateFile(name) {
    return path.join(buildDir, name);
  },
  print: (...args) => console.log('[x2t]', ...args),
  printErr: (...args) => console.error('[x2t-err]', ...args),
};

vm.createContext(context);
vm.runInContext(fs.readFileSync(x2tJs, 'utf8'), context, { filename: x2tJs });

const Module = context.Module;

function mkdirp(dir) {
  const parts = dir.split('/').filter(Boolean);
  let current = '';
  for (const part of parts) {
    current += `/${part}`;
    try {
      Module.FS.mkdir(current);
    } catch {
      // Directory already exists.
    }
  }
}

Module.onRuntimeInitialized = () => {
  mkdirp('/tmp/x2t-conversion');
  mkdirp('/working/fonts');
  mkdirp('/working/themes');
  mkdirp('/server/FileConverter/bin');

  Module.FS.writeFile('/working/in.html', Buffer.from(html, 'utf8'));
  Module.FS.writeFile('/working/params.xml', `<?xml version="1.0" encoding="utf-8"?>
<TaskQueueDataConvert xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">
  <m_sFileFrom>/working/in.html</m_sFileFrom>
  <m_sThemeDir>/working/themes</m_sThemeDir>
  <m_sAllFontsPath>/server/FileConverter/bin/AllFonts.js</m_sAllFontsPath>
  <m_sTempDir>/tmp/x2t-conversion</m_sTempDir>
  <m_sFileTo>/working/out.md</m_sFileTo>
  <m_bIsNoBase64>true</m_bIsNoBase64>
  <m_nFormatFrom>70</m_nFormatFrom>
  <m_nFormatTo>92</m_nFormatTo>
  <m_sFontDir>/working/fonts/</m_sFontDir>
</TaskQueueDataConvert>`);

  const rc = Module.ccall('main1', 'number', ['string'], ['/working/params.xml']);
  if (rc !== 0) {
    console.error(`HTML -> MD failed with x2t code ${rc}`);
    process.exit(1);
  }

  const output = Buffer.from(Module.FS.readFile('/working/out.md')).toString('utf8');
  if (!output.trim()) {
    console.error('Empty Markdown output.');
    process.exit(1);
  }

  if (usingDefaultHtml && (!output.includes('Hello') || !output.includes('[world]') || !output.includes('https://example.com'))) {
    console.error('Unexpected Markdown output:');
    console.error(JSON.stringify(output));
    process.exit(1);
  }

  console.log(output);
};
