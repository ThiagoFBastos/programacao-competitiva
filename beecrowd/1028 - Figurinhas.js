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

function gcd(a, b) {
	if(b === 0) return a;
	return gcd(b, a % b);
}

rl.on('close', () => {
	let t = parseInt(readLine());
	while(t-- > 0) {
		const [a, b] = readLine().split(' ').map(x => parseInt(x));
		console.log(gcd(a, b));	
	}
});