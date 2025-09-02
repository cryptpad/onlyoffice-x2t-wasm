const path = require('node:path');
const fs = require('node:fs');
const { exit } = require('node:process');
const xml2json = require('xml2json');

const WASM = Symbol('WASM');
const BIN = Symbol('BIN');

const getFormatId = function (ext) {
  // Sheets
  if (ext === 'xlsx') { return 257; }
  if (ext === 'xls') { return 258; }
  if (ext === 'ods') { return 259; }
  if (ext === 'csv') { return 260; }
  if (ext === 'pdf') { return 513; }
  // Docs
  if (ext === 'docx') { return 65; }
  if (ext === 'doc') { return 66; }
  if (ext === 'odt') { return 67; }
  if (ext === 'txt') { return 69; }
  if (ext === 'html') { return 70; }

  // Slides
  if (ext === 'pptx') { return 129; }
  if (ext === 'ppt') { return 130; }
  if (ext === 'odp') { return 131; }

  return;
};

const getFromId = function (ext) {
  var id = getFormatId(ext);
  if (!id) { return ''; }
  return '<m_nFormatFrom>'+id+'</m_nFormatFrom>';
};

const getToId = function (ext) {
  var id = getFormatId(ext);
  if (!id) { return ''; }
  return '<m_nFormatTo>'+id+'</m_nFormatTo>';
};

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

function convert(inputPath, outputPath) {
  initWorkDir();
  const inputName = path.basename(inputPath);
  const outputName = path.basename(outputPath);
  const inputFormat = path.extname(inputPath).substring(1);
  const outputFormat = path.extname(outputPath).substring(1);
  const pdfData = "";

  console.log(inputPath, '->', outputPath);
  const params =  "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
    + "<TaskQueueDataConvert xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">"
    + "<m_sFontDir>/working/fonts/</m_sFontDir>"
    + "<m_sThemeDir>/working/themes</m_sThemeDir>"
    + "<m_sFileFrom>/working/" + inputName + "</m_sFileFrom>"
    + "<m_sFileTo>/working/" + outputName + "</m_sFileTo>"
    + pdfData
    // + getFromId(inputFormat)
    // + getToId(outputFormat)
    + "<m_bIsNoBase64>false</m_bIsNoBase64>"
    + "<m_nCsvTxtEncoding>46</m_nCsvTxtEncoding>"
    + "<m_nCsvDelimiter>4</m_nCsvDelimiter>"
    // + "<m_sCsvDelimiterChar>,</m_sCsvDelimiterChar>"
    + "</TaskQueueDataConvert>";

  x2t.FS.writeFile('/working/params.xml', params);
  copyToWasm(inputPath, '/working/' + inputName);

  const result = x2t.ccall("main1", "number", ["string"], ["/working/params.xml"]);
  if (result !== 0) {
    console.log({inputPath, outputPath, inputName, outputName, inputFormat, outputFormat});
    console.log('x2t exit code:', result);
    raise `Converting ${inputPath} -> ${outputPath} failed with exit code ${result}`;
  }
  copyFromWasm('/working/' + outputName, outputPath);
}

function callX2T(workdir, x2tkind) {
  
}

const TEST_CONVERSIONS = {
  '.docx': ['.docx', '.odt'],
  '.xlsx': ['.xlsx', '.ods'],
  '.pptx': ['.pptx', '.odp'],
  '.odt': ['.docx', '.odt'],
  '.ods': ['.xlsx', '.ods'],
  '.odp': ['.pptx', '.odp'],
};

function testConvertDir(inputPath) {
  const paramsXml = fs.readFileSync(path.join(inputPath, 'working', 'params.xml'));
  const paramsJson = JSON.parse(xml2json.toJson(paramsXml));
  let outputPath = paramsJson["TaskQueueDataConvert"]["m_sFileTo"];

  const baseName = path.parse(inputPath).base;
  const ext = path.parse(outputPath).ext;

  initWorkDir();
  copyDirToWasm(inputPath, '/');

  console.log(inputPath, '->', outputPath);
  const result = x2t.ccall("main1", "number", ["string"], ["/working/params.xml"]);
  if (result !== 0) {
    console.log({inputPath, outputPath, baseName});
    console.log('x2t exit code:', result);
    throw `Converting ${inputPath} -> ${outputPath} failed with exit code ${result}`;
  }
  const resultPath = path.join('results', baseName + ext);
  copyFromWasm(outputPath, resultPath);
}

function testConversions(inputPath) {
  if (fs.statSync(inputPath).isDirectory() && path.parse(inputPath).base !== 'fonts') {
    testConvertDir(inputPath);
    return;
  }
  const inputExt = path.extname(inputPath);
  const inputName = path.basename(inputPath, inputExt);
  const conversions = TEST_CONVERSIONS[inputExt];
  if (!conversions) {
    return;
  }
  const binPath = path.join('results', inputName + '.bin');
  convert(inputPath, binPath)
  for (const ext of conversions) {
    convert(binPath, path.join('results', inputName + ext));
  }
}

function testFilesInDir(dir) {
  const files = fs.readdirSync(dir);
  for (const file of files) {
    testConversions(path.join(dir, file));
  }
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
  } catch(e) {
    console.error(e);
    exit(1);
  }
};
