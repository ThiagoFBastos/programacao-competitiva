impl Solution {
    pub fn missing_number(nums: Vec<i32>) -> i32 {
        let mut xor = i32::default();
        let n: usize = nums.len();

        for i in 0..=n {
            xor ^= i as i32;
        }

        for value in nums.into_iter() {
            xor ^= value;
        }

        return xor;
    }
}