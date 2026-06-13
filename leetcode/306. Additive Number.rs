impl Solution {
    pub fn is_additive_number(num: String) -> bool {
        let n = num.len();
        let str = num.chars().collect::<Vec<_>>();
        let mut number = vec![vec![None; n]; n];

        for i in 0..n {
            let mut val = 0;

            for j in i..n {
                let digit = str[j].to_digit(10).unwrap() as i128;
                val = 10 * val + digit;
                number[i][j] = Some(val);
            }

            if str[i] == '0' {
                for j in (i + 1)..n {
                    number[i][j] = None;
                }
            }
        }

        const INF: i32 = 1_000_000_000;
        let mut dp = vec![vec![vec![-INF; n]; n]; n];
        let mut is_possible = false;

        for i in 0..n {
            for j in (i+1)..n {
                if number[0][i].is_some() && number[i+1][j].is_some() {
                    dp[0][i][j] = 2;
                }
            }
        }

        'a:for i in 0..n {
            for j in i..n {
                for k in (j+1)..n {
                    for l in (k + 1)..n {
                        let v1 = number[i][j];
                        let v2 = number[j + 1][k];
                        let v3 = number[k + 1][l];

                        if let Some(a) = v1 && let Some(b) = v2 && let Some(c) = v3 && a + b == c {
                            dp[j + 1][k][l] = std::cmp::max(dp[j + 1][k][l], dp[i][j][k] + 1);
                            if dp[j + 1][k][l] >= 3 && l == n - 1 {
                                is_possible = true;
                                break 'a;
                            }
                        }
                    }
                }
            }
        }

        is_possible
    }
}