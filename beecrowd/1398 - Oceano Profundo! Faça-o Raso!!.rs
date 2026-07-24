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

    const MOD: i32 = 131071;

    let mut modulo = 0;

    while sc.has_next() {
        let s = sc.next::<String>();

        let chars = s.chars().collect::<Vec<_>>();

        for c in chars {
            if !c.is_ascii_digit() {
                continue;
            }

            let digit = c as i32 - '0' as i32;

            modulo = (2 * modulo + digit) % MOD;
        }

        if s.ends_with("#") {
            if modulo != 0 {
                writeln!(writer, "NO").ok();
            } else {
                writeln!(writer, "YES").ok();
            }

            modulo = 0;
        }
    }
}
