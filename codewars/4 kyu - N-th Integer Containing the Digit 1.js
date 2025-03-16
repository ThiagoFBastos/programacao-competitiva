function numbersWithOne(n) {  
    let dp = [0, 0];
    
    let p = 1n, wich = 0;
    
    while(p <= n) p *= 10n;
    
    dp[0] = 1;
    
    while(p > 1) {
      let new_dp = [0, 0];
  
      p = p / 10n;
      
      let cur_d = parseInt(n / p % 10n);
  
      for(let a = 0; a < 2; ++a) {
          let less = 1 + cur_d - (cur_d >= 1), greater = 9 - cur_d - (1 > cur_d); 
          new_dp[a] += dp[a] * less;
          new_dp[a] += (dp[a] - (wich == a ? 1 : 0)) * greater;
          new_dp[1] += dp[a] - (1 > cur_d && wich == a ? 1 : 0);
      }
      
      wich = wich == 1 || cur_d == 1 ? 1 : 0;
      dp = new_dp;
    }
    
    return dp[1];
  }
  
  function nthNumContainingOnes(n) {
    
    let lo = 1n, hi = 1n;
    
    while(numbersWithOne(hi) < n) {
      lo = hi;
      hi *= 2n;
    }
  
    while(lo < hi) {
      let mid = (lo + hi) >> 1n;
      if(numbersWithOne(mid) >= n) hi = mid;
      else lo = mid + 1n;
    }
   
    return parseInt(hi);
  }