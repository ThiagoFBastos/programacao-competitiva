impl Solution {
    pub fn reverse_bits(x: u32) -> u32 {
        let mut answer: u32 = u32::default();
        let mut target = x;

        for i in 1..=32 {
            answer <<= 1;
            answer += target & 1;
            target >>= 1;
        }

        return answer;
    }
}