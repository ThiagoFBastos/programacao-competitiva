impl Solution {
    pub fn first_missing_positive(nums: Vec<i32>) -> i32 {
        let mut arr = nums;
        let n = arr.len() as i32;

        for i in 0..=n - 1 {
            loop {
                let k = arr[i as usize];
                if k >= 1 && k <= n && arr[(k - 1) as usize] != k {
                    let tmp = arr[(k - 1) as usize];
                    arr[(k - 1) as usize] = k;
                    arr[i as usize] = tmp;
                } else {
                    break;
                }
            }
        }

        for i in 0..=n - 1 {
            let k = arr[i as usize];
            
            if k != i + 1 {
                return i + 1;
            }
        }

        return n + 1;
    }
}