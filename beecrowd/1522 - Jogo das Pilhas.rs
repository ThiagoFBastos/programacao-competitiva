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

    const N: usize = 100 + 5;
    const INF: i32 = 1_000_000_000;

    let mut dp = vec![vec![vec![false; N]; N]; N];

    loop {
        let n = sc.next::<usize>().unwrap();

        if n == 0 {
            break;
        }

        let mut heaps = (0..3).map(|_| Vec::with_capacity(n)).collect::<Vec<_>>();

        for grid2d in dp.iter_mut().take(n + 1) {
            for grid1d in grid2d.iter_mut().take(n + 1) {
                for val in grid1d.iter_mut().take(n + 1) {
                    *val = false;
                }
            }
        }

        dp[0][0][0] = true;

        for _ in 0..n {
            for heap in heaps.iter_mut() {
                let val = sc.next::<i32>().unwrap();
                heap.push(val);
            }
        }

        let mut queue = VecDeque::new();

        queue.push_back((0, 0, 0));

       while let Some((i, j, k)) = queue.pop_front() {
            
            for mask in 1..8 {
                let mut pos = [i, j, k];
                let mut sum = 0;

                for (bit, p) in pos.iter_mut().enumerate() {
                    if (mask >> bit) & 1 == 1 && *p < n {
                        sum += heaps[bit][*p];
                        *p += 1;
                    }
                }

                let next = &mut dp[pos[0]][pos[1]][pos[2]];

                if sum % 3 == 0 && !*next {
                    *next = true;
                    queue.push_back((pos[0], pos[1], pos[2]));
                }
            }
        }

        let answer = if dp[n][n][n] { 1 } else { 0 };

        writeln!(writer, "{}", answer).ok();
    }
}
