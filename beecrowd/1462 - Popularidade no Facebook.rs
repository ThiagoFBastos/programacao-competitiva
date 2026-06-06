#![allow(dead_code)]
use std::cmp::Reverse;
use std::collections::VecDeque;
use std::io::{self, BufRead, Error, ErrorKind, Write};

struct Scanner {
    buffer: VecDeque<String>,
    reader: io::BufReader<io::Stdin>,
}

impl Scanner {
    fn new() -> Self {
        Self {
            buffer: VecDeque::new(),
            reader: io::BufReader::new(io::stdin()),
        }
    }

    fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
        if self.buffer.is_empty() {
            let mut input = String::new();

            match self.reader.read_line(&mut input) {
                Ok(0) => {
                    return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
                }
                Ok(_) => {}
                Err(e) => {
                    return Err(e);
                }
            }

            self.buffer = input.split_whitespace().map(|x| x.to_string()).collect();

            if self.buffer.is_empty() {
                self.buffer.push_back("".to_string());
            }
        }

        let front = self.buffer.pop_front().unwrap();

        Ok(front.parse::<T>().ok().unwrap())
    }
}

fn erdos_gallai(deg: &[i32]) -> bool {
    let n = deg.len();
    let mut degrees = deg.to_vec();

    degrees.sort_by_key(|d| Reverse(*d));

    let mut left_sum = degrees.iter().map(|d| *d as i64).sum::<i64>();
    let mut right_sum = 0;
    let mut cnt_right = 0;
    let mut is_possible = left_sum % 2 == 0;
    let mut next = vec![0; n + 1];

    for (i, val) in next.iter_mut().enumerate() {
        *val = i + 1;
    }

    for i in (1..=n).rev() {
        if !is_possible {
            break;
        }

        let mut cur = i + 1;

        while cur <= n && degrees[cur - 1] >= i as i32 {
            right_sum -= degrees[cur - 1] as i64;
            cnt_right += 1;
            cur = next[cur];
        }

        next[i] = cur;

        let k = i as i64;

        is_possible = is_possible && left_sum <= k * (k - 1) + right_sum + cnt_right * k;

        left_sum -= degrees[i - 1] as i64;
        right_sum += degrees[i - 1] as i64;
    }

    is_possible
}

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    loop {
        let inp = sc.next::<usize>();

        if inp.is_err() {
            break;
        }

        let n = inp.unwrap();

        let degrees = (0..n)
            .map(|_| sc.next::<i32>().unwrap())
            .collect::<Vec<_>>();

        if erdos_gallai(&degrees) {
            writeln!(writer, "possivel").ok();
        } else {
            writeln!(writer, "impossivel").ok();
        }
    }
}
