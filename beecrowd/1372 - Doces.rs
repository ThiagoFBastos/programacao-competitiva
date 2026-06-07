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

    const N: usize = 100_000 + 5;

    let mut grid = vec![0; N];
    let mut dp = vec![[0; 2]; N];
    let mut dp_row = vec![[0; 2]; N];

    loop {
        let n = sc.next::<usize>().unwrap();
        let m = sc.next::<usize>().unwrap();

        if n == 0 {
            break;
        }

        for i in 0..n {
            for j in 0..m {
                grid[i * m + j] = sc.next::<i32>().unwrap();
            }
        }

        dp[0][0] = 0;
        dp[0][1] = i32::MIN as i64;

        for i in 0..n {
            dp_row[0][0] = 0;
            dp_row[0][1] = grid[i * m] as i64;

            for j in 1..m {
                let val = grid[i * m + j] as i64;

                dp_row[j][0] = std::cmp::max(dp_row[j - 1][0], dp_row[j - 1][1]);
                dp_row[j][1] = val + dp_row[j - 1][0];
            }

            let row = std::cmp::max(dp_row[m - 1][0], dp_row[m - 1][1]);

            dp[i + 1][0] = std::cmp::max(dp[i][0], dp[i][1]);
            dp[i + 1][1] = row + dp[i][0];
        }

        writeln!(writer, "{}", std::cmp::max(dp[n][0], dp[n][1])).ok();
    }
}
