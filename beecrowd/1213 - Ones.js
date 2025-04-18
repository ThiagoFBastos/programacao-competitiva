#!/usr/bin/env node

const readline = require('readline');

const rl = readline.createInterface({
	input: process.stdin,
	output: process.stdout
});

const lines = [];

rl.on('line', (line) => {
    lines.push(line);
});

let lineCur = 0;
function readLine() {
	return lines[lineCur++];
}

function isEOF() {
	return lineCur == lines.length;
}

function phi(n) {
	let x = n;
	for(let p = 2; p * p <= n; ++p) {
		if(n % p != 0) continue;
		x -= x / p;	
		while(n % p == 0) n /= p;	
	}
	if(n != 1) x -= x/n;
	return x;
}

function expMod(a, b, m) {
	let x = 1;
	for(; b > 0; b >>= 1) {
		if((b & 1) == 1) x = x * a % m;
		a = a * a % m;
	}
	return x;
}

rl.on('close', () => {
	while(!isEOF()) {
		let n = parseInt(readLine());
		n *= 9;
		let eu = phi(n), k = n;
		for(let i = 1; i * i <= eu; ++i) {
			if(eu % i != 0) continue;
			if(expMod(10, i, n) == 1 && k > i) k = i;
			if(expMod(10, eu / i, n) == 1 && k > eu / i) k = eu / i;
		}
		console.log(k);
	}
});