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
}

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    let t = sc.next::<usize>().unwrap();

    for i in 1..=t {
        let n = sc.next::<usize>().unwrap();
        let m = sc.next::<usize>().unwrap();
        let castle = sc.next::<usize>().unwrap() - 1;

        let mut adj = vec![vec![]; n];
        let mut damage = vec![0; n];

        for _ in 0..m {
            let u = sc.next::<usize>().unwrap() - 1;
            let v = sc.next::<usize>().unwrap() - 1;

            adj[u].push(v);
            adj[v].push(u);
        }

        let towers = sc.next::<usize>().unwrap();

        let mut dist = vec![None; n];
        let mut queue = VecDeque::new();

        for _ in 0..towers {
            let v = sc.next::<usize>().unwrap() - 1;
            let attack = sc.next::<i64>().unwrap();
            let distance = sc.next::<i32>().unwrap();

            for d in dist.iter_mut() {
                *d = None;
            }

            queue.clear();

            queue.push_back(v);
            dist[v] = Some(0);

            while let Some(v) = queue.pop_front() {
                let d = dist[v].unwrap();

                damage[v] += attack;

                if d == distance {
                    continue;
                }

                for &u in &adj[v] {
                    if dist[u].is_some() || u == castle {
                        continue;
                    }

                    dist[u] = Some(d + 1);
                    queue.push_back(u);
                }
            }
        }

        let mut needed_life = vec![i64::MAX; n];
        let mut pq = BinaryHeap::new();

        pq.push(Reverse((0, castle)));
        needed_life[castle] = 0;

        while let Some(Reverse((total_damage, v))) = pq.pop() {
            if needed_life[v] != total_damage {
                continue;
            }

            for &u in &adj[v] {
                let life = damage[u] + total_damage;

                if life < needed_life[u] {
                    needed_life[u] = life;
                    pq.push(Reverse((life, u)));
                }
            }
        }

        let queries = sc.next::<usize>().unwrap();
        let mut alive = 0;

        for _ in 0..queries {
            let v = sc.next::<usize>().unwrap() - 1;
            let life = sc.next::<i64>().unwrap();

            if needed_life[v] < life {
                alive += 1;
            }
        }

        writeln!(writer, "Caso #{}: {}", i, alive).ok();
    }
}
