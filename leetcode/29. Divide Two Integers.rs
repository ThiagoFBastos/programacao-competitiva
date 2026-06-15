impl Solution {
    fn multiply(mut lhs: i64, rhs: i64) -> i64 {
        let mut result = 0;
        let mut pow = 0;

        while lhs > 0 {
            let bit = lhs & 1;

            if bit == 1 {
                result += rhs << pow;
            }

            pow += 1;
            lhs >>= 1;
        }

        result
    }

    pub fn divide(dividend: i32, divisor: i32) -> i32 {
        let mut p = (dividend as i64).abs();
        let q = (divisor as i64).abs();
        let mut d = 0;

        while p != 0 {
            let i = 63 - p.abs().leading_zeros();
            let j = 63 - q.leading_zeros();

            if i < j {
                break;
            }

            let k = i - j;
            let pow = 1_i64 << k;

            if p < 0 {
                d -= pow;
                p += q << k;
            } else {
                d += pow;
                p -= q << k;
            }
        }

        
        if Self::multiply((divisor as i64).abs(),  d + 1) <= (dividend as i64).abs() {
            d += 1;
        } else if Self::multiply((divisor as i64).abs(), d) > (dividend as i64).abs() {
            d -= 1;
        } 

        if dividend < 0 {
            d = -d;
        }

        if divisor < 0 {
            d = -d;
        }

        d = d.clamp(i32::MIN as i64, i32::MAX as i64);

        d as i32
    }
}