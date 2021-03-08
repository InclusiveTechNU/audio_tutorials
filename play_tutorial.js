const fs = require('fs');
const v11 = require ('../v11/bazel-bin/v11/typescript/v11.js');
const process = require('process');

let rawdata = fs.readFileSync('tutorial.json');
let tutorial = JSON.parse(rawdata);

let intervalsLeft = tutorial.length;

for (const tutorialPart of tutorial) {
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
                console.log("done");
                clearInterval(tutorialPartId);
            }
            
            if (intervalsLeft === 0) {
                console.log('You finished the tutorial!');
                process.exit(0);
            }
        }
    }, 100);
}
