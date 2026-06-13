use std::collections::BinaryHeap;

impl Solution {
    pub fn max_sliding_window(nums: Vec<i32>, k: i32) -> Vec<i32> {
        let n = nums.len();
        let window = k as usize;
        let mut pq = BinaryHeap::new();
        let mut max = Vec::with_capacity(n);

        for (idx, val) in nums.into_iter().enumerate() {
            pq.push((val, idx));

            while pq.len() > window && pq.peek().unwrap().1 <= idx - window {
                pq.pop();
            }

            if idx >= window - 1 {
                max.push(pq.peek().unwrap().0);
            }
        }

        max
    }
}