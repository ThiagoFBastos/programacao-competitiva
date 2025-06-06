impl Solution {
    pub fn three_sum_closest(nums: Vec<i32>, target: i32) -> i32 {
        let n = nums.len();
        let mut closest = i32::default();
        let mut diff = i32::MAX;

        let mut arr = nums.clone();

        arr.sort();

        for i in 0..=n - 1 {
            let mut hi = n;

            for j in i + 1..=n - 1 {

                while hi - 1 > j && arr[i] + arr[j] + arr[hi - 1] >= target {
                    hi -= 1;
                }

                if hi < n {
                    let sum = arr[i] + arr[j] + arr[hi];

                    if (sum - target).abs() < diff {
                        closest = sum;
                        diff = (sum - target).abs();
                    }
                }

                if hi - 1 > j {
                    let sum = arr[i] + arr[j] + arr[hi - 1];

                    if (sum - target).abs() < diff {
                        closest = sum;
                        diff = (sum - target).abs();
                    }
                }
            }
        }

        return closest;
    }
}