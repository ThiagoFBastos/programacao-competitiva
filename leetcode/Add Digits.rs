impl Solution {
    pub fn add_digits(num: i32) -> i32 {
        if num == 0 {
            return 0;
        }
        
        let root = num % 9;
        return if root > 0 { root } else { 9 };
    }
}