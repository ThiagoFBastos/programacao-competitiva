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

    let t = sc.next::<usize>();

    for _ in 0..t {
        let d = sc.next::<u64>();

        let mut digits = (0..d).map(|_| sc.next::<char>()).collect::<Vec<_>>();

        digits.sort();
        digits.dedup();

        let mut n = sc.next::<u64>();

        let mut kth = Vec::new();

        while n > 0 {
            let digit = (n - 1) % d;
            kth.push(digits[digit as usize]);
            n = (n - digit) / d;
        }

        kth.reverse();

        let answer = kth.iter().collect::<String>();

        writeln!(writer, "{}", answer).ok();
    }
}
