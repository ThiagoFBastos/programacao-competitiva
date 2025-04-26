const input = require('fs').readFileSync('/dev/stdin', 'utf8');
const lines = input.split('\n');

let lineCur = 0;

function readLine() {
    return lines[lineCur++];
}

function eof() {
    return lineCur == lines.length - 1;
}

while(!eof()) {
    const [a, b] = readLine().split(' ').map(x => BigInt(x));
    console.log((a ^ b).toString());
}
