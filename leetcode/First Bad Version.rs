// The API isBadVersion is defined for you.
// isBadVersion(version:i32)-> bool;
// to call it use self.isBadVersion(version)

impl Solution {
    pub fn first_bad_version(&self, n: i32) -> i32 {
        let mut lo: i32 = 0;
        let mut hi: i32 = n;

        while lo < hi {
            let mid = (((lo as i64) + (hi as i64)) / 2) as i32;

            if self.isBadVersion(mid) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }

        return hi;
    }
}