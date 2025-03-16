function multiply(n, k) {
    k = parseInt(k);

    let p = [], groups = 0;
      
    if(n % 2n == 0) {
        let j = 0;
        while(n % 2n == 0) {
            n /= 2n;
            ++j;
        }
        p.push(j);
        groups += j;
    }

    for(let i = 3; i * i <= n; i += 2) {
        let pk = BigInt(i);
        if(n % pk != 0) continue;    
        let j = 0;
        while(n % pk == 0) {
            n /= pk;
            ++j;
        }
        p.push(j);
        groups += j;
    }

    if(n != 1n) {
        p.push(1);
        ++groups;
    }

    groups = Math.min(groups, k);

    let m = p.length;
    let fat = new Array(2 * k + 1);
    let dp = new Array(groups + 1).fill(BigInt(0));

    fat[0] = 1n;

    for(let i = 1; i <= 2 * Math.max(k, 40); ++i) fat[i] = fat[i - 1] * BigInt(i);

    let C = (n, k) => n < k || k < 0 ? 0n : fat[n] / (fat[n - k] * fat[k]);

    dp[groups] = 1n;

    for(let pow of p) {
        let tmp = new Array(groups + 1).fill(BigInt(0));
        for(let i = 0; i <= groups; ++i) {
            for(let j = 0; j <= pow && j <= i; ++j) {
                let k = pow - j;
                let g = groups - i + j;
                tmp[i - j] += dp[i] * C(i, j) * C(g + k - 1, g - 1);
            }
       }
       dp = tmp;
    }

    let cnt = 0n;

    for(let i = 0; i <= groups; ++i) {
        let merges = C(groups, i);
        let ways = dp[i] / merges * C(k, groups - i);
        cnt += ways;
    }
 
    return cnt;
}