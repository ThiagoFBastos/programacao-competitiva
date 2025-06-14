impl Solution {
    pub fn is_perfect_square(num: i32) -> bool {
        let mut x: i64 = 1;

        while x * x < (num as i64) {
            x += 1;
        }

        return x * x == (num as i64);
    }
}