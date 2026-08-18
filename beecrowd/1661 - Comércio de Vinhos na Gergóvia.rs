#![allow(dead_code)]
use std::{
    collections::VecDeque,
    io::{self, Read, Write},
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

    while sc.has_next() {
        let n = sc.next::<usize>();

        if n == 0 {
            break;
        }

        let mut buy = VecDeque::new();
        let mut buy_quantity = 0;
        let mut sell = VecDeque::new();
        let mut sell_quantity = 0;
        let mut steps = 0;

        let quantity = (0..n).map(|_| sc.next::<i32>()).collect::<Vec<_>>();

        for mut q in quantity {
            steps += buy_quantity + sell_quantity;

            if q > 0 {
                while let Some(wines) = sell.pop_back() {
                    let remain = wines - q;

                    sell_quantity -= wines as i64;
                    q -= wines;

                    if remain > 0 {
                        sell.push_back(remain);
                        sell_quantity += remain as i64;
                        break;
                    }
                }

                if q > 0 {
                    buy.push_back(q);
                    buy_quantity += q as i64;
                }
            } else if q < 0 {
                q *= -1;

                while let Some(wines) = buy.pop_back() {
                    let remain = wines - q;

                    buy_quantity -= wines as i64;
                    q -= wines;

                    if remain > 0 {
                        buy.push_back(remain);
                        buy_quantity += remain as i64;
                        break;
                    }
                }

                if q > 0 {
                    sell.push_back(q);
                    sell_quantity += q as i64;
                }
            }
        }

        writeln!(writer, "{}", steps).ok();
    }
}
