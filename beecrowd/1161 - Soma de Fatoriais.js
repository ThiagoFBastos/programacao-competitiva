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

function fat(n) {
    if(n < 2) return 1n;
    return BigInt(n) * fat(n - 1);
}

while(!eof()) {
    const [n, m] = readLine().split(' ').map(x => parseInt(x));
    let ans = fat(n) + fat(m);
    console.log(ans.toString());
}