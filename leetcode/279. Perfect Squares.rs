impl Solution {
    pub fn num_squares(n: i32) -> i32 {
        let m = n as usize;
        let mut i = 1;
        let mut dp = vec![n; m + 1];

        dp[0] = 0;
        
        while i * i <= m {
            let square = i * i;
            for j in 0..=(m - square) {
                let next = j + square;
                dp[next] = std::cmp::min(dp[next], dp[j] + 1);
            }
            i += 1;
        }

        dp[m]
    }
}