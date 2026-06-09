#![allow(dead_code)]
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

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    const N: usize = 4950 + 5;

    let mut dp = vec![false; N];

    loop {
        let token = sc.next::<usize>();

        if token.is_err() {
            break;
        }

        let n = token.unwrap();
        let m = sc.next::<usize>().unwrap();

        let mut deg = vec![0; n];

        for val in dp.iter_mut().take(m + 1) {
            *val = false;
        }

        for _ in 0..m {
            let u = sc.next::<usize>().unwrap() - 1;
            let v = sc.next::<usize>().unwrap() - 1;

            deg[u] += 1;
            deg[v] += 1;
        }

        dp[0] = true;

        for &d in &deg {
            for j in (0..=m).rev() {
                if d + j <= m {
                    dp[d + j] = dp[d + j] || dp[j];
                }
            }
        }

        writeln!(writer, "{}", if dp[m] { 'S' } else { 'N' }).ok();
    }
}
