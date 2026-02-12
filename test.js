const test = require('node:test');
const assert = require('node:assert').strict;
const fs = require('node:fs');
const path = require('node:path');
const child_process = require('node:child_process');
const os = require('node:os');

test('convert a file', (t) => {
    testConvert('/test/tests/Test Import.ods', 'test.bin');
});

function testConvert(inputFile, outputBase) {
    const workdir = prepareWorkdir();
    const inputBase = path.parse(inputFile).base;
    const inputPath = path.join(workdir, inputBase);
    const outputPath = path.join(workdir, outputBase);
    fs.cpSync(inputFile, inputPath);
    writeParamsXml(workdir, inputPath, outputPath);

    const child = child_process.spawnSync(`node x2t-wasm.js ${workdir}`, {shell: true});
    console.log('stdout', child.stdout.toString('utf8'));
    console.log('stderr', child.stderr.toString('utf8'));
    assert.equal(child.status, 0);
}

function writeParamsXml(workdir, inputPath, outputPath) {
    const inputName = path.basename(inputPath);
    const outputName = path.basename(outputPath);

    const params = `<?xml version=\"1.0\" encoding=\"utf-8\"?>
        <TaskQueueDataConvert xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">
        <m_sFontDir>${path.join(workdir, 'fonts')}</m_sFontDir>
        <m_sThemeDir>${path.join(workdir, 'themes')}</m_sThemeDir>
        <m_sFileFrom>${inputName}</m_sFileFrom>
        <m_sFileTo>${outputName}</m_sFileTo>
        <m_bIsNoBase64>false</m_bIsNoBase64>
        <m_nCsvTxtEncoding>46</m_nCsvTxtEncoding>
        <m_nCsvDelimiter>4</m_nCsvDelimiter>
        </TaskQueueDataConvert>`;

    fs.writeFileSync(path.join(workdir, 'params.xml'), params);
}

function prepareWorkdir() {
    const dir = fs.mkdtempSync(path.join(os.tmpdir(),'x2t-test-'));
    fs.mkdirSync(path.join(dir, 'media'));
    fs.mkdirSync(path.join(dir, 'themes'));
    fs.cpSync('/test/tests/fonts', path.join(dir, 'fonts'), { recursive: true });
    return dir;
}
