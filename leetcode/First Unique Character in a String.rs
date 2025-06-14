use std::collections::HashMap;

impl Solution {
    pub fn first_uniq_char(s: String) -> i32 {
        let chars: Vec<char> = s.chars().collect();
        let mut has_char = [0; 26];
        let n = s.len();

        for i in (0..n) {
            let index = (chars[i] as usize) - ('a' as usize);
            has_char[index] += 1;
        }

        for i in (0..n) {
            let index = (chars[i] as usize) - ('a' as usize);

            if has_char[index] == 1 {
                return i as i32;
            }
        }

        return -1;
    }
}