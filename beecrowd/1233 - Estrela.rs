#![allow(dead_code)]
use std::{
    io::{self, Read, Write},
    writeln,
};

struct Scanner {
    buffer: Vec<u8>,
    index: usize,
}

impl Scanner {
    fn new() -> Self {
        let mut input = Vec::new();

        io::stdin().read_to_end(&mut input).unwrap();

        Self {
            buffer: input,
            index: 0,
        }
    }

    fn has_next(&mut self) -> bool {
        while self.index < self.buffer.len() && self.buffer[self.index].is_ascii_whitespace() {
            self.index += 1;
        }

        self.index < self.buffer.len()
    }

    fn next<T: std::str::FromStr>(&mut self) -> T {
        if !self.has_next() {
            panic!("End Of File");
        }

        let start = self.index;

        while self.index < self.buffer.len() && !self.buffer[self.index].is_ascii_whitespace() {
            self.index += 1;
        }

        std::str::from_utf8(&self.buffer[start..self.index])
            .unwrap()
            .parse::<T>()
            .ok()
            .unwrap()
    }
}

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    const N: usize = 46345;

    let mut is_prime = vec![true; N];

    for p in 2..N {
        if p * p > N {
            break;
        } else if !is_prime[p] {
            continue;
        }

        for i in ((p * p)..N).step_by(p) {
            is_prime[i] = false;
        }
    }

    let primes = (2..N).filter(|n| is_prime[*n]).collect::<Vec<_>>();

    let phi = move |mut n: usize| {
        let mut answer = n;
        let lim = n as i64;

        for &p in &primes {
            let a = p as i64;

            if a * a > lim {
                break;
            } else if n % p != 0 {
                continue;
            }

            while n % p == 0 {
                n /= p;
            }

            answer -= answer / p;
        }

        if n > 1 {
            answer -= answer / n;
        }

        answer
    };

    while sc.has_next() {
        let n = sc.next::<usize>();
        let tot = phi(n);
        let answer = (tot + 1) / 2;
        writeln!(writer, "{}", answer).ok();
    }
}
