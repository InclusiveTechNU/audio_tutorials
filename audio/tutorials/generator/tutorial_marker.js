const fs = require('fs');
const WAVPlayer = require('node-wav-player');
const iohook = require('./iohook/index.js');

const tutorialFileName = 'tutorial';
const tutorialJSONExt = 'json';
const tutorialWAVExt = 'wav';
const tutorialJSONFilePath = `${tutorialFileName}.${tutorialJSONExt}`;
const tutorialWAVFilePath = `${tutorialFileName}.${tutorialWAVExt}`;

// Load tutorial metadata for adding markers
const tutorialJSONRaw = fs.readFileSync(tutorialJSONFilePath);
let tutorialMetaData = JSON.parse(tutorialJSONRaw);
tutorialMetaData['markers'] = new Array();

// Load and play tutorial audio overlay
WAVPlayer.play({
    path: tutorialWAVFilePath,
    sync: true
}).then(() => {
    // When audio is completed export tutorial metadata to tutorial json file
    fs.writeFileSync('tutorial.json', JSON.stringify(tutorialMetaData));
    process.kill( process.pid, 'SIGTERM' );
});

const startDateTime = new Date();
const startTime = startDateTime.getTime();

// Add marker times when [space] key is pressed
iohook.registerShortcut([57], (_) => {
    const cutDateTime = new Date();
    const cutTime = cutDateTime.getTime();
    const timeDifference = cutTime - startTime;
    tutorialMetaData['markers'].push(timeDifference);
});
iohook.start();
