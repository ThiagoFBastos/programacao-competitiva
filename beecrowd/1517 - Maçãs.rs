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

    const INF: i32 = 1_000_000_000;

    let distance = |(x0, y0): (usize, usize), (x1, y1): (usize, usize)| {
        let mut x_delta = std::cmp::max(x0, x1) - std::cmp::min(x0, x1);
        let mut y_delta = std::cmp::max(y0, y1) - std::cmp::min(y0, y1);

        if x_delta < y_delta {
            y_delta -= x_delta;
        } else {
            x_delta -= y_delta;
        }

        x_delta + y_delta
    };

    loop {
        let n = sc.next::<usize>().unwrap();
        let m = sc.next::<usize>().unwrap();
        let k = sc.next::<usize>().unwrap();

        if n == 0 && m == 0 && k == 0 {
            break;
        }

        let mut apples = Vec::with_capacity(k + 1);

        for _ in 0..k {
            let x = sc.next::<usize>().unwrap();
            let y = sc.next::<usize>().unwrap();
            let t = sc.next::<usize>().unwrap();

            apples.push((x, y, t));
        }

        let x0 = sc.next::<usize>().unwrap();
        let y0 = sc.next::<usize>().unwrap();

        apples.insert(0, (x0, y0, 0));

        let mut dp = vec![-INF; k + 1];

        dp[0] = 0;

        for (i, apple) in apples.iter().enumerate().skip(1) {
            let (xf, yf, tf) = *apple;

            for (j, apple) in apples.iter().take(i).enumerate() {
                let (xi, yi, ti) = *apple;
                let d = distance((xi, yi), (xf, yf));

                if d <= tf - ti {
                    dp[i] = std::cmp::max(dp[i], dp[j] + 1);
                }
            }
        }

        let answer = dp.iter().max().unwrap();

        writeln!(writer, "{}", answer).ok();
    }
}
