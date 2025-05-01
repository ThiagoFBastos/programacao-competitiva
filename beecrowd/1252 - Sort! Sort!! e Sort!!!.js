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
	while(true) {
		const [n, m] = readLine().split(' ').map(x => parseInt(x));
		if(n + m == 0) break;
		let a = new Array(n);
		for(let i = 0; i < n; ++i) a[i] = parseInt(readLine());
		a.sort((p, q) => {
			if(p % m != q % m) return p % m - q % m;
			if((p & 1) != (q & 1)) return ((p+1)&1) - ((q+1)&1);
			return p % 2 == 0 ? p - q : q - p;
		});
		console.log(n, m);
		for(let i in a) console.log(a[i]);
	}
	console.log('0 0');
});