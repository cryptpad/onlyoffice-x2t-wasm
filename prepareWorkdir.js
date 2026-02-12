const fs = require('node:fs');

function prepareWorkdir() {
    const dir = fs.mkdtempSync('x2t-test');
    fs.mkdirSync(path);
}
