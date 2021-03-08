const iohook = require('iohook');
const v11 = require ('../v11/bazel-bin/v11/typescript/v11.js');
const fs = require('fs');
const process = require('process');

function captureSnapshot(element) {
    let snapshot = {
        label: element.label,
        type: element.type,
        title: element.title,
        value: element.value,
        helpText: element.helpText,
        children: []
    }
    const children = element.children;
    for (const child of children) {
        snapshot['children'].push(captureSnapshot(child));
    }
    return snapshot;
}

function matchChildren(newChildren, oldChildren) {
    let result = [];
    if (newChildren.length === oldChildren.length) {
        for (let i = 0; i < newChildren.length; i++) {
            result.push([newChildren[i], oldChildren[i]]);
        }
        return result;
    }
    let newChildIndex = 0;
    let oldChildIndex = 0;
    while (newChildIndex < newChildren.length && oldChildIndex < oldChildren.length) {
        let newChild = newChildren[newChildIndex];
        let oldChild = oldChildren[oldChildIndex];
        if (newChild.type !== oldChild.type) {
            result.push([newChild, undefined]);
            newChildIndex++;
        } else {
            result.push([newChild, oldChild]);
            oldChildIndex++;
            newChildIndex++;
        }
    }
    return result;
}

function getDifferences(newSnapshot, originalSnapshot) {
    let differences = [];
    if (newSnapshot.value !== originalSnapshot.value) {
        differences.push({
            label: newSnapshot.label,
            title: newSnapshot.title,
            change: 'value',
            old: originalSnapshot.value,
            new: newSnapshot.value,
        });
    }
    if (newSnapshot.title !== originalSnapshot.title) {
        differences.push({
            label: newSnapshot.label,
            title: newSnapshot.title,
            change: 'title',
            old: originalSnapshot.title,
            new: newSnapshot.title,
        });
    }

    if (newSnapshot.helpText !== originalSnapshot.helpText) {
        differences.push({
            label: newSnapshot.label,
            title: newSnapshot.title,
            change: 'help',
            old: originalSnapshot.helpText,
            new: newSnapshot.helpText,
        });
    }

    if (newSnapshot.children.length > 0) {
        const matchedChildren = matchChildren(newSnapshot.children, originalSnapshot.children);
        for (let i = 0; i < matchedChildren.length; i++) {
            if (matchedChildren[i][1] !== undefined) {
                differences = differences.concat(getDifferences(matchedChildren[i][0], matchedChildren[i][1]));
            }
        }
    }
    return differences;
}

const garageband = v11.system.getApplicationByName('GarageBand');
let originalSnapshot = captureSnapshot(garageband.windows[1]);
console.log('Ready to run!');

let differences = [];

iohook.registerShortcut([56, 32], (_) => {
    console.log('Creating tutorial!');
    const newSnapshot = captureSnapshot(garageband.windows[1]);
    differences = differences.concat(getDifferences(newSnapshot, originalSnapshot));
    const differencesString = JSON.stringify(differences);
    fs.writeFileSync('tutorial.json', differencesString);
    console.log('Exported tutorial!');
    process.kill( process.pid, 'SIGTERM' );
});

iohook.on('keyup', (_) => {
    const newSnapshot = captureSnapshot(garageband.windows[1]);
    differences = differences.concat(getDifferences(newSnapshot, originalSnapshot));
    originalSnapshot = newSnapshot;
});

iohook.start();
