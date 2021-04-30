const fs = require('fs');
const WAVPlayer = require('node-wav-player');
const v11 = require ('../v11/bazel-bin/v11/typescript/v11.js');
const process = require('process');

const waitForEvents = (sections, index) => {
    if (sections.length >= index+1) {
        const section = sections[index];
        setTimeout(() => {
            WAVPlayer.stop();
        }, section.marker);

        let intervalsLeft = section.events.length;
        for (const tutorialPart of section.events) {
            // Doing this until tommy publishes accessibility listeners
            let tutorialPartId = 0;
            tutorialPartId = setInterval(function(){
                const garageband = v11.system.getApplicationByName('GarageBand');
                const components = garageband.getElementsByLabel(tutorialPart.label);
                if (components.length > 0) {
                    const component = components[0];
                    const valueChange = tutorialPart.change === 'value' && tutorialPart.new === component.value;
                    const titleChange = tutorialPart.change === 'title' && tutorialPart.new === component.title;
                    const helpChange = tutorialPart.change === 'help' && tutorialPart.new === component.helpText;
                    if (valueChange || titleChange || helpChange) {
                        intervalsLeft--;
                        clearInterval(tutorialPartId);
                    }
                    if (intervalsLeft === 0) {
                        console.log(`Finished section: ${index+1}`);
                        waitForEvents(sections, index+1);
                    }
                }
            }, 100);
        }
    } else {
        console.log('You finished the tutorial!');
        process.exit(0);
    }
};

let rawdata = fs.readFileSync('tutorial.json');
let tutorialMetaData = JSON.parse(rawdata);

let tutorialSections = new Array();
let lastEventIndex = -1;
for (const tutorialMarker of tutorialMetaData['markers']) {
    const tutorialEvents = [];
    for (let i = lastEventIndex+1; i < tutorialMetaData['differences'].length; i++) {
        const tutorialEvent = tutorialMetaData['differences'][i];
        if (tutorialEvent.time <= tutorialMarker) {
            tutorialEvents.push(tutorialEvent);
            lastEventIndex = i;
        } else {
            break;
        }
    }
    tutorialSections.push({
        marker: tutorialMarker,
        events: tutorialEvents
    });
}

const tutorialFileName = 'tutorial';
const tutorialWAVExt = 'wav';
const tutorialWAVFilePath = `${tutorialFileName}.${tutorialWAVExt}`;
WAVPlayer.play({
    path: tutorialWAVFilePath,
});

waitForEvents(tutorialSections, 0);
