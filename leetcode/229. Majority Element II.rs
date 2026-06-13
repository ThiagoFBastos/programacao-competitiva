use std::collections::HashMap;

impl Solution {
    pub fn majority_element(nums: Vec<i32>) -> Vec<i32> {
        let n = nums.len();
        let mut frequency = HashMap::new();

        for &val in &nums {
            frequency.insert(val, *frequency.get(&val).unwrap_or(&0) + 1);
        }

        let majority = frequency.iter()
            .filter(|(k, v)| **v > n / 3)
            .map(|(k, v)| *k).collect::<Vec<_>>();

        majority
    }
}