const v11 = require ('../v11/bazel-bin/v11/typescript/v11.js');
const garageband = v11.system.getApplicationByName('GarageBand');

garageband.getElementsByLabel('Volume')[0].addEventListener('value', () => {
    console.log("Hello");
});

console.log(garageband.getElementsByLabel('Volume')[0]);
