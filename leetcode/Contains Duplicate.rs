use std::collections::HashSet;

impl Solution {
    pub fn contains_duplicate(nums: Vec<i32>) -> bool {
        let mut st: HashSet<i32> = HashSet::new();

        for val in nums.into_iter() {
            if st.contains(&val) {
                return true;
            }

            st.insert(val);
        }

        return false;
    }
}