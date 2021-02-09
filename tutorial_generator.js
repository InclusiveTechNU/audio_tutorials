const iohook = require('../iohook/index.js');
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

function getDifferences(newSnapshot, originalSnapshot) {
    let differences = [];
    if (newSnapshot.value !== originalSnapshot.value) {
        const difference = {
            label: newSnapshot.label,
            title: newSnapshot.title,
            oldValue: originalSnapshot.value,
            newValue: newSnapshot.value,
        };
        console.log(difference);
        differences.push(difference);
    }
    if (newSnapshot.children.length > 0) {
        for (let i = 0; i < newSnapshot.children.length; i++) {
            const newChild = newSnapshot.children[i];
            const child = originalSnapshot.children[i];
            differences += getDifferences(newChild, child);
        }
    }
    return differences;
}

const garageband = v11.system.getApplicationByName('GarageBand');
const tracksHeader = garageband.getElementsByLabel("Tracks header")[0];
const tracksHeaderSnapshot = captureSnapshot(tracksHeader);

const id = iohook.registerShortcut([29, 65], (keys) => {
    const newTracksHeader = garageband.getElementsByLabel("Tracks header")[0];
    const newSnapshot = captureSnapshot(newTracksHeader);
    const differences = getDifferences(newSnapshot, tracksHeaderSnapshot)
});

iohook.start();
