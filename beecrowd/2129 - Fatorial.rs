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

fn decomp(mut n: i32) -> (i64, i64, i64) {
    let mut cnt_2 = 0;
    let mut cnt_5 = 0;

    while n % 2 == 0 {
        n /= 2;
        cnt_2 += 1;
    }

    while n % 5 == 0 {
        n /= 5;
        cnt_5 += 1;
    }

    (n as i64, cnt_2, cnt_5)
}

fn bin_exp(mut n: i64, mut p: i64, m: i64) -> i64 {
    let mut answer = 1;

    while p > 0 {
        if p & 1 == 1 {
            answer = answer * n % m;
        }

        n = n * n % m;
        p >>= 1;
    }

    answer
}

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    const N: usize = 1_000_005;

    let mut fat_mod = vec![0; N];
    let mut n2 = vec![0; N];
    let mut n5 = vec![0; N];

    fat_mod[1] = 1;

    for i in 2..N {
        let (n, cnt_2, cnt_5) = decomp(i as i32);
        fat_mod[i] = fat_mod[i - 1] * n % 10;
        n2[i] = n2[i - 1] + cnt_2;
        n5[i] = n5[i - 1] + cnt_5;
    }

    let mut tc = 1;

    while sc.has_next() {
        let n = sc.next::<usize>();

        let answer = fat_mod[n] * bin_exp(2, n2[n] - n5[n], 10) % 10;

        writeln!(writer, "Instancia {}", tc).ok();
        writeln!(writer, "{}", answer).ok();
        writeln!(writer).ok();

        tc += 1;
    }
}
