function totalIncDec(x){
    if(x == 0) return 1;
    let m = x + 9;
    let fat = new Array(m + 1).fill(BigInt(0));
    fat[0] = 1n;
    for(let i = 1; i <= m; ++i) fat[i] = fat[i - 1] * BigInt(i);
    let C = (n, k) => fat[n] / (fat[k] * fat[n - k]);
    let cnt = C(x + 9, 9);
    for(let d = 1; d <= x; ++d) cnt += C(d + 9, 9) - 10n;
    return parseInt(cnt);
}