const mod = 12345787n;

function binExp(n, k) {
    let ans = 1n;
    for(; k > 0n; k >>= 1n) {
        if(k % 2n == 1n) ans = ans * n % mod;
        n = n * n % mod;
    }
    return ans;
}

function C(n, k) {
    let a = 1n, b = 1n;
    for(let i = 1n; i <= k; ++i) {
        a = a * (n - i + 1n) % mod;
        b = b * i % mod;
    }
    return a * binExp(b, mod - 2n) % mod;
}

function insaneIncOrDec(maxDigits) {
    let ans = C(maxDigits + 9n, 9n) - 1n + C(maxDigits + 10n, 10n) - 9n * maxDigits - C(maxDigits + 1n, 1n);
    return (ans % mod + mod) % mod;
}