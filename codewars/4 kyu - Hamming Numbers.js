let num = [], a = 1n, b, c;

for(let i = 0; i < 50; ++i) {
b = 1n;
for(let j = 0; j < 40; ++j) {
    c = 1n;
    for(let k = 0; k < 40; ++k) {
        num.push(a * b * c);    
        c *= 5n;
    }
    b *= 3n;
}
a *= 2n;   
}

num.sort((a, b) => {
    if(a < b) return -1;
    else if(a > b) return 1;
    return 0;
});

function hamming(n) {
    return num[n - 1];
}