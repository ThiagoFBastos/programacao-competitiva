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

function ord(c) {
	let alpha = "abcdefghijklmnopqrstuvwxyz";
	for(let i = 0; i < 26; ++i) if(alpha[i] == c) return i;
	return -1;
}

function chr(c) {
	let alpha = "abcdefghijklmnopqrstuvwxyz";
	return alpha[c];
}

rl.on('close', () => {
	const t = parseInt(readLine());
	function dfs(adj, marked, u, lst) {
		marked[u] = true;
		lst.push(u);
		for(let i = 0; i < adj[u].length; ++i) {
			let v = adj[u][i];
			if(marked[v]) continue;
			dfs(adj, marked, v, lst);	
		}
	}
	for(let c = 1; c <= t; ++c) {
		const [v, e] = readLine().split(' ').map(x => parseInt(x));
		let adj = new Array(v);
		let marked = new Array(v);
		marked.fill(false);
		for(let i = 0; i < v; ++i) adj[i] = [];
		for(let i = 0; i < e; ++i) {
			const [a, b] = readLine().split(' ');	
			const [u, v] = [ord(a), ord(b)];
			adj[u].push(v);
			adj[v].push(u);
		}
		console.log("Case #" + c + ':');
		let cc = 0;
		for(let i = 0; i < v; ++i) {
			if(marked[i]) continue;
			++cc;
			let lst = [], out = '';
			dfs(adj, marked, i, lst);
			lst.sort((a,b) => a-b);
			for(let j = 0; j < lst.length; ++j) out += chr(lst[j]) + ',';
			console.log(out);
		}
		console.log(cc + ' connected components');
		console.log();
	}
});