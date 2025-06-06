use std::collections::HashSet;

impl Solution {
    pub fn four_sum(nums: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
        let mut arr = nums.clone();
        let n = nums.len();
        let mut quadruplets: Vec<Vec<i32>> = vec![];
        let mut st: HashSet<(i32, i32, i32, i32)> = HashSet::new();

        arr.sort();

        for i in 0..=n-1 {
            for j in i+1..=n-1 {
                let mut hi = n;

                for k in j+1..=n-1 {

                    while hi - 1 > k && arr[i] + arr[j] + arr[k] + arr[hi - 1] >= target {
                        hi -= 1;
                    }

                    if hi <= k {
                        hi = k + 1;
                    }

                    if hi == n {
                        continue;
                    }

                    let sum: i64 = (arr[i] as i64) + (arr[j] as i64) + (arr[k] as i64) + (arr[hi] as i64);

                    if sum == (target as i64) && !st.contains(&(arr[i], arr[j], arr[k], arr[hi])) {
                        st.insert((arr[i], arr[j], arr[k], arr[hi]));
                        quadruplets.push([arr[i], arr[j], arr[k], arr[hi]].to_vec());
                    }
                }
            }
        }

        return quadruplets;
    }
}