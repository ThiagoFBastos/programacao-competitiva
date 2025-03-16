function largestPower(n, p) {
    let k = 0;
    while(n > 0) {
        n = (n - n % p) / p;
        k += n;
    }
    return k;
}

function trailingZeros(num, base) {
    if(num == 0) return 1;
    let factors = [];
    let trailing = Number.MAX_VALUE;

    for(let p = 2; p * p <= base; ++p) {
        if(base % p != 0) continue;
        let k = 0;
        while(base % p == 0) {
            base /= p;
            ++k;
        }
        factors.push([p, k]);
    }

    if(base != 1) factors.push([base, 1]);
    
    for(const [p, k] of factors) {
        let i = largestPower(num, p);
        trailing = Math.min(trailing, (i - i % k) / k);
    }

    return trailing;
}