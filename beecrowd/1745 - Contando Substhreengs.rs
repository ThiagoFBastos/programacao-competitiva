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

    let s = sc.next::<String>();

    let mut cnt = [0; 3];
    let mut sum = 0;
    let mut answer = 0;

    cnt[0] = 1;

    for digit in s.chars() {
        if !digit.is_ascii_digit() {
            sum = 0;
            cnt = [1, 0, 0];
            continue;
        }

        let d = digit.to_digit(10).unwrap() as usize;

        sum = (sum + d) % 3;
        answer += cnt[sum];
        cnt[sum] += 1_i64;
    }

    writeln!(writer, "{}", answer).ok();
}
