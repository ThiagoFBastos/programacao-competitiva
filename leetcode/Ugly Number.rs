impl Solution {
    pub fn is_ugly(n: i32) -> bool {
        if n == 0 {
            return false;
        }
        
        let mut target = n;

        while target % 2 == 0 {
            target /= 2;
        }

        while target % 3 == 0 {
            target /= 3;
        }

        while target % 5 == 0 {
            target /= 5;
        }

        return target == 1;
    }
}