impl Solution {
    pub fn gray_code(mut n: i32) -> Vec<i32> {
        let mut code = (0..(1 << n))
                        .map(|i| i ^ (i >> 1))
                        .collect::<Vec<_>>();
        code
    }
}