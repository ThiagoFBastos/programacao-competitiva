function countChange(money, coins) {
    let dp = new Array(money + 1).fill(0);
    dp[money] = 1;
    for(let c of coins)
      for(let i = money; i >= c; --i) dp[i - c] += dp[i]
    return dp[0];
  }