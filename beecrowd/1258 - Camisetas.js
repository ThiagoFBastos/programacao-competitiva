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

let is_first_test_case = true;

while(true) {
    const n = parseInt(readLine());

    if(n == 0) break;

    let pessoas = [];

    for(let i = 0; i < n; ++i) {
        const nome = readLine();
        const [cor, tamanho] = readLine().split(' ');
        pessoas[i] = {nome, cor, tamanho};
    }

    const tamanhos = ['P', 'M', 'G'];

    pessoas.sort((a, b) => {
        if(a.cor != b.cor) {
            if(a.cor < b.cor) return -1;
            return a.cor > b.cor ? 1 : 0;
        } else if(a.tamanho != b.tamanho) return tamanhos.indexOf(a.tamanho) - tamanhos.indexOf(b.tamanho);
        else if(a.nome < b.nome) return -1;
        return a.nome > b.nome ? 1: 0;
    });

    if(!is_first_test_case) console.log();

    is_first_test_case = false;

    for(const {nome, cor, tamanho} of pessoas)
        console.log(`${cor} ${tamanho} ${nome}`);
}