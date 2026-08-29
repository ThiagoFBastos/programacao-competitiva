impl Solution {
    pub fn is_scramble(s1: String, s2: String) -> bool {
        let n = s1.len();
        let m = s2.len();
        let a = s1.chars().collect::<Vec<_>>();
        let b = s2.chars().collect::<Vec<_>>();
        let mut dp = vec![vec![vec![vec![None; m]; m]; n]; n];

        for i in 0..n {
            for j in 0..m {
                dp[i][i][j][j] = Some(a[i] == b[j]);
            }
        }

        fn recursive_dp(dp: &mut [Vec<Vec<Vec<Option<bool>>>>], la: usize, ra: usize, a: &[char], lb: usize, rb: usize, b: &[char]) -> bool {
            if let Some(answer) = dp[la][ra][lb][rb] {
                return answer;
            } else if ra - la != rb - lb {
                dp[la][ra][lb][rb] = Some(false);
                return false;
            }

            dp[la][ra][lb][rb] = Some(false);

            for i in la..ra {    
                let answer = (recursive_dp(dp, i + 1, ra, a, lb, lb + ra - i - 1, b) && recursive_dp(dp, la, i, a, lb + ra - i, rb, b))
                || (recursive_dp(dp, la, i, a, lb, lb + i - la, b) && recursive_dp(dp, i + 1, ra, a, lb + i - la + 1, rb, b));

                if answer {
                    dp[la][ra][lb][rb] = Some(answer);
                    break;
                }
            }

            dp[la][ra][lb][rb].unwrap()
        }

        recursive_dp(&mut dp, 0, n - 1, &a, 0, m - 1, &b)
    }
}