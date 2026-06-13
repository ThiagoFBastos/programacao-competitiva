use std::collections::BTreeSet;

impl Solution {
    pub fn subsets_with_dup(mut nums: Vec<i32>) -> Vec<Vec<i32>> {
        let n = nums.len();
        let m = 1 << n;
        let mut subsets = BTreeSet::new();

        nums.sort();

        for mask in 0..m {
            let mut set = Vec::new();

            for j in 0..n {
                if (mask >> j) & 1 == 1 {
                    set.push(nums[j]);
                }
            }

            subsets.insert(set);
        }

        subsets.into_iter().collect::<Vec<Vec<_>>>()
    }
}