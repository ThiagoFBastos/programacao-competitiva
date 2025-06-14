use std::collections::HashSet;

impl Solution {
    pub fn intersection(nums1: Vec<i32>, nums2: Vec<i32>) -> Vec<i32> {
        let mut a: HashSet<i32> = nums1.into_iter().collect();
        let mut b: HashSet<i32> = nums2.into_iter().collect();
        let intersection: HashSet<i32> = a.intersection(&b).cloned().collect();
        let answer: Vec<i32> = intersection.into_iter().collect();
        
        return answer;
    }
}