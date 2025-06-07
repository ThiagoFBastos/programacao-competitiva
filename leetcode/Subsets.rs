impl Solution {
    pub fn subsets(nums: Vec<i32>) -> Vec<Vec<i32>> {
        let mut subsets: Vec<Vec<i32>> = vec![];
        let n = nums.len();

        for i in 0..=(1 << n) - 1 {
            let mut set: Vec<i32> = vec![];

            for j in 0..=n - 1 {
                if ((i >> j) & 1) == 1 {
                    set.push(nums[j]);
                }
            }

            subsets.push(set);
        }

        return subsets;
    }
}