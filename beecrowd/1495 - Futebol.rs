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

    const N: usize = 105;

    while sc.has_next() {
        let n = sc.next::<i32>();
        let g = sc.next::<i32>();

        let mut needed = [0; N];
        let mut wins = 0;

        for _ in 0..n {
            let s = sc.next::<usize>();
            let r = sc.next::<usize>();

            if s > r {
                wins += 1;
            } else {
                needed[r - s] += 1;
            }
        }

        let mut points = 3 * wins;
        let mut bought = 0;

        'a: for (i, &need) in needed.iter().enumerate() {
            for _ in 0..need {
                let j = i as i32;

                if bought + j < g {
                    bought += j + 1;
                    points += 3;
                } else if bought + j <= g {
                    bought += j;
                    points += 1;
                } else if i == 0 {
                    points += 1;
                } else {
                    break 'a;
                }
            }
        }

        writeln!(writer, "{}", points).ok();
    }
}
