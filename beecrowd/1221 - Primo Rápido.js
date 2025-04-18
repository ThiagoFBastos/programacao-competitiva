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

rl.on('close', () => {
	let t = parseInt(readLine());

	let is_prime = function(x) {
		if(x == 1) return false;
		for(let p = 2; p * p <= x; ++p) {
			if(x % p == 0) return false;
		}
		return true;
	};	

	while(t-- > 0) {
		let x = parseInt(readLine());
		console.log(is_prime(x) ? 'Prime' : 'Not Prime');
	}
});