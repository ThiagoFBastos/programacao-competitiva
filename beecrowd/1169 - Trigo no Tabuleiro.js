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
    let x = parseInt(readLine());   

    let tot = (2n ** BigInt(x) - 1n) / 12000n;

    console.log(tot.toString() + " kg");
}