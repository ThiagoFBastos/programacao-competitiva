#!/usr/bin/env node

var input = require('fs').readFileSync('/dev/stdin', 'utf8');
var lines = input.split('\n');

let lineCur = 0;

function readLine() {
    return lines[lineCur++];
}

function eof() {
    return lineCur == lines.length - 1;
}

const [n, x] = readLine().split(' ').map(x => parseInt(x));

let arr = readLine().split(' ').map(x => parseInt(x));

arr.sort((a, b) => a - b);

let ans = 1;

for(let i = 1; i < n; ++i) {
    if(arr[i] + arr[i - 1] > x) break;
    ans = i + 1;
}

console.log(ans);