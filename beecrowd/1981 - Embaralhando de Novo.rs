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

    const N: usize = 10000 + 5;
    const MOD: i64 = 100000007;
    const ALPHABET: usize = 26;

    let mut fat = vec![1; N];
    let mut inv = vec![1; N];
    let mut inv_fat = vec![1; N];

    for i in 2..N {
        let j = i as i64;

        fat[i] = j * fat[i - 1] % MOD;
        inv[i] = (MOD - MOD / j) * inv[(MOD % j) as usize] % MOD;
        inv_fat[i] = inv[i] * inv_fat[i - 1] % MOD;
    }

    while sc.has_next() {
        let s = sc.next::<String>();

        if s == "0" {
            break;
        }

        let mut frq = [0; ALPHABET];

        for c in s.chars() {
            let index = c as usize - 'a' as usize;
            frq[index] += 1;
        }

        let mut answer = fat[s.len()];

        for i in 0..26 {
            answer = answer * inv_fat[frq[i]] % MOD;
        }

        writeln!(writer, "{}", answer).ok();
    }
}
