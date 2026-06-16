impl Solution {
    pub fn maximum_gap(mut nums: Vec<i32>) -> i32 {
        let mut gap = 0;
        let n = nums.len();

        nums.sort();

        for i in 1..n {
            gap = std::cmp::max(gap, nums[i] - nums[i - 1]);
        }

        gap
    }
}