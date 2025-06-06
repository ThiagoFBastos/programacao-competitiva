impl Solution {
    fn reverse_number(x: i32) -> i32 {
        let mut z = x;
        let mut y = 0;
        let mut negative = false;

        if z < 0 {
            negative = true;
        }

        z = z.abs();

        while z > 0 { 
            y *= 10;
            y += z % 10;
            z /= 10;
        }

        if negative {
            y *= -1;
        }

        return y;
    }

    pub fn reverse(x: i32) -> i32 {
        let ans = Solution::reverse_number(x);
        let mut y = x;

        while y.abs() > 0 && y % 10 == 0 {
            y /= 10;
        }

        if Solution::reverse_number(ans) != y {
            return 0;
        }

        return ans;
    }
}