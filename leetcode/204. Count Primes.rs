impl Solution {
    pub fn count_primes(n: i32) -> i32 {
        let m = n as usize;
        let mut is_prime = vec![true; m];

        for i in 0..m.min(2) {
            is_prime[i] = false;
        }

        for p in 2..m {
            if p * p >= m {
                break;
            }

            for i in (p*p..m).step_by(p) {
                is_prime[i] = false;
            }
        }

        let count = is_prime.iter().filter(|v| **v).count();

        count as i32
    }
}