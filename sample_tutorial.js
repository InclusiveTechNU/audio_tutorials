const iohook = require('iohook');
const v11 = require ('../v11/bazel-bin/v11/typescript/v11.js');

function captureSnapshot(element) {
    let snapshot = {
        label: element.label,
        title: element.title,
        value: element.value,
        children: []
    }
    const children = element.children;
    for (const child of children) {
        snapshot['children'].push(captureSnapshot(child));
    }
    return snapshot;
}

const garageband = v11.system.getApplicationByName('GarageBand');
const windowChildren = garageband.windows[1].children;
const gbSnapshot = [];
for (const child of windowChildren) {
    gbSnapshot.push(captureSnapshot(child));
}

console.log(gbSnapshot);