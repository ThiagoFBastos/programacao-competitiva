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

    while sc.has_next() {
        let r = sc.next::<usize>();
        let c = sc.next::<usize>();
        let k = sc.next::<usize>();

        if r + c + k == 0 {
            break;
        }

        let mut prefix = Vec::with_capacity(r);

        for _ in 0..r {
            let line = sc.next::<String>();

            let mut row = vec![0; c + 1];

            for (j, c) in line.chars().enumerate() {
                row[j + 1] = row[j];

                if c == '.' {
                    row[j + 1] += 1;
                }
            }

            prefix.push(row);
        }

        let mut min_area = i32::MAX;

        for left in 0..c {
            for right in left..c {
                let mut lo = 0;
                let mut cnt = 0;

                for i in 0..r {
                    cnt += prefix[i][right + 1] - prefix[i][left];

                    while cnt + prefix[lo][left] - prefix[lo][right + 1] >= k {
                        cnt -= prefix[lo][right + 1] - prefix[lo][left];
                        lo += 1;
                    }

                    if cnt >= k {
                        let area = (i - lo + 1) * (right - left + 1);
                        min_area = std::cmp::min(min_area, area as i32);
                    }
                }
            }
        }

        writeln!(writer, "{}", min_area).ok();
    }
}
