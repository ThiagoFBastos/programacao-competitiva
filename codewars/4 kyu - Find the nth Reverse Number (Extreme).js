function findReverseNumber(n) {
    if(n <= 10) return n - 1;
    --n;
    let len = 1;
    while(true) {
        let mid = (len + 1) >> 1;
        let cnt = 9 * 10 ** (mid - 1);
        if(n <= cnt) break;
        n -= cnt;
        ++len;
    }
    console.log(len, n);
    let mid = (len + 1) >> 1;
    let target = (10n ** BigInt(mid - 1) + BigInt(n - 1)).toString();
    return BigInt(target + target.substr(0, mid - len % 2).split('').reverse().join(''));
}