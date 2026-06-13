impl Solution {
    pub fn count_digit_one(mut n: i32) -> i32 {
        let mut rem = 1_i64;
        let mut pow = 1_i64;
        let mut ones = 0_i64;
        let mut i = 0_i64;
        
        while n > 0 {
            let digit = (n % 10) as i64;
            ones += digit * (pow / 10) * i;

            if digit == 1 {
                ones += rem;
            } else if digit > 1 {
                ones += pow;
            }

            rem += digit * pow;
            pow *= 10;
            n /= 10;
            i += 1;
        }

        ones as i32
    }
}