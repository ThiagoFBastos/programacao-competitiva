use std::collections::HashMap;

impl Solution {
    pub fn longest_valid_parentheses(s: String) -> i32 {
        let n = s.len();
        let mut st: Vec<(i32, usize)> = vec![];
        let mut mp: HashMap<i32, Vec<usize>> = HashMap::new();
        let mut prefix = vec![0; n + 1];
        let mut max_substring = usize::default();

        let texto: Vec<char> = s.chars().collect();

        mp.entry(0).or_insert(Vec::new()).push(0);

        for i in 1..=n {
            prefix[i] = prefix[i - 1];

            if texto[i - 1] == '(' {
                prefix[i] += 1;
            } else {
                prefix[i] -= 1;
            }

            mp.entry(prefix[i]).or_insert(Vec::new()).push(i);
        }

        st.push((i32::MIN, n + 1));
        st.push((prefix[prefix.len() - 1], n));

        for i in (1..(n+1)).rev() {
            while st.len() > 0 && st[st.len() - 1].0 >= prefix[i - 1] {
                st.pop();
            }
            
            let pos = st[st.len() - 1].1;

            let positions = mp.get(&prefix[i - 1]).unwrap();

            let index = positions.binary_search(&pos);

            match index {
                Ok(k) | Err(k) => {
                    let length = 1 + positions[k - 1] - i;

                    if max_substring < length {
                        max_substring = length;
                    }
                }
            };

            st.push((prefix[i - 1], i - 1));
        }

        return max_substring as i32;
    }
}