#!/bin/bash

cd iohook
npm install || error=1
node build.js --upload=false
