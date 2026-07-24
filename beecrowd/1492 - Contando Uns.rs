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

fn counting_bits(mut n: i64) -> i64 {
    let mut ones = 0;
    let mut remainder = 1;
    let mut power_of_two = 1;
    let mut i = 0;

    while n > 0 {
        ones += (n & 1) * (remainder + (power_of_two >> 1) * i);
        remainder += (n & 1) * power_of_two;
        power_of_two <<= 1;
        n >>= 1;
        i += 1;
    }

    ones
}

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    while sc.has_next() {
        let lo = sc.next::<i64>();
        let hi = sc.next::<i64>();

        let bits = counting_bits(hi) - counting_bits(lo - 1);

        writeln!(writer, "{}", bits).ok();
    }
}
