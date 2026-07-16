#![allow(dead_code)]
use std::io::{self, Read, Write};

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

    fn next<T: std::str::FromStr>(&mut self) -> T {
        while self.index < self.buffer.len() && self.buffer[self.index].is_ascii_whitespace() {
            self.index += 1;
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

    const MOD: u64 = 1_000_000_007;

    let n = sc.next::<usize>();

    let values = (0..n).map(|_| sc.next::<u64>()).collect::<Vec<_>>();

    let mut bits = [0; 64];

    for value in values {
        for (i, bit) in bits.iter_mut().enumerate() {
            if value & 1 << i != 0 {
                *bit += 1;
            }
        }
    }

    let mut answer = 0;

    for i in 1..=n {
        for (j, &bit) in bits.iter().enumerate() {
            if bit > 0 && (bit & i) == i {
                answer += 1_u64 << j;
            }

            answer %= MOD;
        }
    }

    writeln!(writer, "{}", answer).ok();
}
