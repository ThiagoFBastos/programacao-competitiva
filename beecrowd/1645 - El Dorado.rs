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

    loop {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();

        if n + m == 0 {
            break;
        }

        let values = (0..n).map(|_| sc.next::<i32>()).collect::<Vec<_>>();
        let mut dp = vec![vec![0; m + 1]; n];

        for i in 0..n {
            dp[i][1] = 1;

            for j in 0..i {
                if values[j] >= values[i] {
                    continue;
                }

                let length = std::cmp::min(m, j + 2);

                for k in 1..=length {
                    dp[i][k] += dp[j][k - 1];
                }
            }
        }

        let answer = dp.iter().map(|row| row[m]).sum::<i64>();

        writeln!(writer, "{}", answer).ok();
    }
}
