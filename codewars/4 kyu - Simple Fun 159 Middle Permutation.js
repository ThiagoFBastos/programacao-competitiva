function fat(n) {
    return n <= 1 ? 1n : BigInt(n) * fat(n - 1);
}

function find(s, k) {
    let base = [0n], t = '';
    alpha = s.split('').sort().join('');
    if(k == 0) return alpha;
    for(let i = 1; k > 0; ++i) {
        let f = k % fat(i + 1) / fat(i);
        base.push(f);
        k -= f * fat(i);
    }
    for(let i = s.length - 1; i >= 0; --i) {
        let c = base[i];
        t += alpha[c];
        alpha = alpha.replace(alpha[c], '');
    }
    return t;
}

function middlePermutation(s) {
    return find(s, fat(s.length) / 2n - 1n);
}