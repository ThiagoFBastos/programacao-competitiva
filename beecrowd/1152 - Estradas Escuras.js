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

const N = 200000 + 10;

let par = new Array(N);
let rank = new Array(N);

function findSet(p) {
	return p == par[p] ? p : par[p] = findSet(par[p]);
}

function join(a, b) {
	a = findSet(a);
	b = findSet(b);
	if(a == b) return false;
	if(rank[a] > rank[b]) {
		let tmp = a;
		a = b;
		b = tmp;
	}
	par[a] = b;
	rank[b] = rank[a] == rank[b] ? rank[a] + 1 : rank[b];
	return true;
}

function initialize(n) {
	for(let i = 0; i < n; ++i) {
		par[i] = i;
		rank[i] = 0;
	}
}

rl.on('close', () => {

	while(true) {
		const [n, m] = readLine().split(' ').map(x => parseInt(x));

		if(n + m == 0) break;
		
		let edges = new Array(n);
		let ans = 0;

		initialize(n);

		for(let i = 0; i < m; ++i) {
			let row = readLine().split(' ');
			let a = parseInt(row[0]), b = parseInt(row[1]), c = parseInt(row[2]);
			edges[i] = {u: a, v: b, weight: c};
			ans += c;
		}

		edges.sort((p, q) => {return p.weight - q.weight});

		for(let i = 0; i < m; ++i) {
			const {u, v, weight} = edges[i];
			if(join(u, v)) ans -= weight;
		}

		console.log(ans);
	}
});