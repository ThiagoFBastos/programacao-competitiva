use std::collections::HashMap;

impl Solution {
    pub fn single_number(nums: Vec<i32>) -> i32 {
        let mut frequency = HashMap::new();

        for val in nums {
            let cnt = *frequency.get(&val).unwrap_or(&0);
            frequency.insert(val, cnt + 1);
        }

        let filtered = frequency.iter().filter(|(k, v)| **v == 1).map(|(k, v)| *k).collect::<Vec<_>>();

        let answer = *filtered.first().unwrap();

        answer 
    }
}