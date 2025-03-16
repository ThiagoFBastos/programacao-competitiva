function solve(s, ops) {
    let n = s.length;
    let dp = new Array(n);  
    for(let i = 0; i < n; ++i) {
        dp[i] = new Array(n);
        for(let j = 0; j < n; ++j) dp[i][j] = new Array(2).fill(0);
        dp[i][i][s[i] == 't' ? 1 : 0] = 1;
    }
    for(let len = 2; len <= n; ++len) {
        for(let l = 0; l + len <= n; ++l) {
            let r = l + len - 1;
            for(let k = l + 1; k <= r; ++k) {
                let op = ops[k - 1];
                for(let a = 0; a < 2; ++a) {
                    for(let b = 0; b < 2; ++b) {
                        let ways = dp[l][k - 1][a] * dp[k][r][b], target;
                        if(op == '&') target = a & b;
                        else if(op == '|') target = a | b;
                        else target = a ^ b;
                        dp[l][r][target] += ways;
                    }
                }
            }
        }
    }
    return dp[0][n - 1][1];
}