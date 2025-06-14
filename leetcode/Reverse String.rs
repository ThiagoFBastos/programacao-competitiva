impl Solution {
    pub fn reverse_string(s: &mut Vec<char>) {
        let mut lo: usize = 0;
        let mut hi: usize = s.len() - 1;

        while lo < hi {
            let tmp = s[lo];
            s[lo] = s[hi];
            s[hi] = tmp;
            lo += 1;
            hi -= 1;
        }
    }
}