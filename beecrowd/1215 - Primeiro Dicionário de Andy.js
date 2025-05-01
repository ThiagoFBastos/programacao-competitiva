#!/usr/bin/env node

var input = require('fs').readFileSync('/dev/stdin', 'utf8');

var lines = input.split('').map(c => {
    c = c.toLowerCase();

    let ascii = c.charCodeAt(0);
    
    if(ascii >= 'a'.charCodeAt(0) && ascii <= 'z'.charCodeAt(0)) return c;
    
    return ' ';
}).join('');

let words = lines.split(' ');

words.sort();

for(let i = 0; i < words.length; ++i) {
    if((i == 0 || words[i] != words[i - 1]) && words[i].length > 0)
        console.log(words[i]);
}