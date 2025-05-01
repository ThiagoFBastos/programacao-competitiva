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

const n = parseInt(readLine());

let arr = [];

for(let i = 0; i < n; ++i)
    arr.push(parseInt(readLine()));

arr.sort((a, b) => {
    if(a % 2 != b % 2) return a % 2 - b % 2;
    else if(a % 2 == 0) return a - b;
    return b - a;
});

const output = arr.map(v => v.toString()).join('\n');

console.log(output);