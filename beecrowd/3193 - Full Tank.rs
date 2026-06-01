#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::Reverse;
use std::collections::{BinaryHeap, VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};

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

    fn read_line(&mut self) -> io::Result<String> {
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

        Ok(input)
    }
}

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    let n = sc.next::<usize>().unwrap();
    let m = sc.next::<usize>().unwrap();

    let mut adj = vec![vec![]; n];

    let cost = (0..n)
        .map(|_| sc.next::<i32>().unwrap())
        .collect::<Vec<_>>();

    for _ in 0..m {
        let u = sc.next::<usize>().unwrap();
        let v = sc.next::<usize>().unwrap();
        let d = sc.next::<usize>().unwrap();

        adj[u].push((v, d));
        adj[v].push((u, d));
    }

    let q = sc.next::<usize>().unwrap();

    for _ in 0..q {
        let c = sc.next::<usize>().unwrap();
        let s = sc.next::<usize>().unwrap();
        let t = sc.next::<usize>().unwrap();

        let mut dp = vec![vec![None; n]; c + 1];
        let mut pq = BinaryHeap::new();

        pq.push(Reverse((0, 0, s)));

        while let Some(Reverse((cst, fuel, u))) = pq.pop() {
            if dp[fuel][u].is_some() {
                continue;
            }

            dp[fuel][u] = Some(cst);

            if u == t {
                break;
            }

            if fuel < c {
                let new_cost = cst + cost[u];

                if dp[fuel + 1][u].is_none() {
                    pq.push(Reverse((new_cost, fuel + 1, u)));
                }
            }

            for &(v, d) in &adj[u] {
                if d <= fuel && dp[fuel - d][v].is_none() {
                    pq.push(Reverse((cst, fuel - d, v)));
                }
            }
        }

        let total_cost = dp.iter().filter_map(|row| row[t]).min();

        if let Some(total_cost) = total_cost {
            writeln!(writer, "{}", total_cost).ok();
        } else {
            writeln!(writer, "impossible").ok();
        }
    }
}
