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

let first = true;

while(!eof()) {
    let str = readLine();

    let ascii = new Array(128);

    for(let i = 0; i < 128; ++i) 
        ascii[i] = {code: i, cnt : 0};

    for(let c of str) {
        let code = c.charCodeAt(0);
        ++ascii[code].cnt;
    }

    ascii.sort((a, b) => {
        if(a.cnt != b.cnt) return a.cnt - b.cnt;
        return a.code < b.code ? 1 : -1;
    });

    if(!first) console.log();

    first = false;
 
    for(const {code, cnt} of ascii) {
        if(cnt == 0) continue;
        console.log(`${code} ${cnt}`);
    }
}