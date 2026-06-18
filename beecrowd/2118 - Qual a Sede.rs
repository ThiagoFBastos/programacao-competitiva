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

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    let places = sc.next::<usize>().unwrap();
    let headquarters = sc.next::<usize>().unwrap();
    let students = sc.next::<usize>().unwrap();
    let streets = sc.next::<usize>().unwrap();

    let mut headquarter = Vec::with_capacity(headquarters);
    let mut graph = vec![vec![]; places];

    for idx in 1..=headquarters {
        let place = sc.next::<usize>().unwrap() - 1;
        let medals = sc.next::<i32>().unwrap();
        let days = sc.next::<i32>().unwrap();

        headquarter.push((place, medals, days, idx));
    }

    headquarter.sort_by_key(|(_, medals, days, _)| Reverse((*medals, *days)));

    for _ in 0..streets {
        let u = sc.next::<usize>().unwrap() - 1;
        let v = sc.next::<usize>().unwrap() - 1;

        graph[u].push(v);
        graph[v].push(u);
    }

    let mut nearest_headquarter = vec![None; places];
    let mut queue = VecDeque::new();

    for &(local, _, _, idx) in &headquarter {
        if nearest_headquarter[local].is_none() {
            nearest_headquarter[local] = Some(idx);
            queue.push_back(local);
        }
    }

    while let Some(u) = queue.pop_front() {
        for &v in &graph[u] {
            if nearest_headquarter[v].is_none() {
                nearest_headquarter[v] = nearest_headquarter[u];
                queue.push_back(v);
            }
        }
    }

    for _ in 0..students {
        let local = sc.next::<usize>().unwrap() - 1;

        if let Some(headquarter) = nearest_headquarter[local] {
            writeln!(writer, "{}", headquarter).ok();
        } else {
            writeln!(writer, "Noic").ok();
        }
    }
}
