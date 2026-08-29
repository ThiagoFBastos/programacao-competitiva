impl Solution {
    pub fn num_decodings(s: String) -> i32 {
        let chars = s.chars().collect::<Vec<_>>();
        let n = s.len();
        let mut dp = vec![0; n + 1];

        dp[0] = 1;

        for i in 0..n {
            if chars[i] != '0' {
                dp[i + 1] += dp[i];

                if i + 1 < n && !(chars[i] > '2' || (chars[i] == '2' && chars[i + 1] > '6')) {
                    dp[i + 2] += dp[i];
                }
            }
        }

        dp[n]
    }
}