#!/usr/bin/env node

const input = require('fs').readFileSync('/dev/stdin', 'utf8');
const lines = input.split('\n');

let lineCur = 0;

function readLine() {
    return lines[lineCur++];
}

function eof() {
    return lineCur == lines.length - 1;
}

const t = parseInt(readLine());

for(let i = 0; i < t; ++i) {
    let c = parseFloat(readLine());   
    let days = 0;

    while(c > 1) {
        c /= 2;
        ++days;
    }

    console.log(`${days} dias`);
}