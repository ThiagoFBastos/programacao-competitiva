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

function countDigits(n, d) {
	let s = n.toString(), cnt = 0, seen = 0;
	let len = s.length;
	if(d == 0) {
		if(len == 1) return 1;
		cnt += (parseInt(s[0]) - 1) * (len - 1) * (10 ** (len - 2));
		for(let i = 1; i < len; ++i) {
			let digit = parseInt(s[i]);
			let res = len - i - 1;
			cnt += digit * (10 ** (res - 1)) * res;
			if(d < digit) cnt += 10**res;
			cnt += seen * digit * (10 ** res);
			if(digit == d) ++seen;
		}
		for(let i = 2; i < len; ++i) cnt += 9 * (i - 1) * (10 ** (i - 2));
		return cnt + seen + 1;
	}
	for(let i = 0; i < len; ++i) {
		let digit = parseInt(s[i]);
		let res = len - i - 1;
		cnt += digit * (10 ** (res - 1)) * res;
		if(d < digit) cnt += 10**res;
		cnt += seen * digit * (10 ** res);
		if(digit == d) ++seen;
	}
	cnt += seen;
	return cnt;
}

rl.on('close', () => {
	while(true) {
		const [l, r] = readLine().split(' ').map(x => parseInt(x));	
		if(l + r == 0) break;
		let output = '';
		for(let i = 0; i <= 9; ++i) {
			output += (countDigits(r, i) - countDigits(l - 1, i)).toString();
			if(i < 9) output += ' ';
		}
		console.log(output);
	}
});