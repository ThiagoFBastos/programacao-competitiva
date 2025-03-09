function countSubsequences(needle, haystack) {
    const mod = 10 ** 8;
    const n = needle.length;
    const m = haystack.length;

    let dp = new Array(n + 5);

    for(let i = 0; i <= n; ++i) dp[i] = new Array(m + 5).fill(0);
  
    dp[0][0] = 1;

    for(let i = 0; i <= n; ++i) {
        for(let j = 0; j <= m; ++j) {
            if(i < n && j < m && needle[i] == haystack[j]) dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % mod;
            dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % mod;
        }
    }

    return dp[n][m];
}