function isInterleave(s1: string, s2: string, s3: string): boolean {
    const n = s1.length;
    const m = s2.length;
    const dp = [];

    if(n + m != s3.length)
        return false;

    for(let i = 0; i <= n; ++i)
        dp[i] = new Array<boolean>(m + 1).fill(false);

    dp[0][0] = true;

    for(let i = 0; i <= n; ++i)
        for(let j = 0; j <= m && i + j <= s3.length; ++j)
            dp[i][j] = dp[i][j] || (i > 0 && s3[i+j-1] == s1[i-1] && dp[i-1][j]) || (j > 0 && s3[i+j-1] == s2[j-1] && dp[i][j - 1]);

    return dp[n][m];
};