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

for(let t = 0; t < n; ++t) {
    const words = readLine().split(' ');
    const m = words.length;

    let arr = new Array(m);

    for(let i = 0; i < m; ++i)
        arr[i] = {word: words[i], ind: i};

    arr.sort((a, b) => {
        if(a.word.length != b.word.length) return b.word.length - a.word.length;
        return a.ind - b.ind;
    });

    
    const sorted_words = arr.map(v => v.word);

    console.log(sorted_words.join(' '));
}