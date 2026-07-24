#![allow(dead_code)]
use std::{
    collections::VecDeque,
    io::{self, Read, Write},
    writeln,
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

    let t = sc.next::<usize>();

    let is_dag = |adj: &[Vec<usize>]| {
        let n = adj.len();
        let mut deg = vec![0; n];
        let mut queue = VecDeque::new();
        let mut reachable = 0;

        for neighbours in adj {
            for &v in neighbours {
                deg[v] += 1;
            }
        }

        for (u, _) in adj.iter().enumerate() {
            if deg[u] == 0 {
                queue.push_back(u);
            }
        }

        while let Some(u) = queue.pop_front() {
            reachable += 1;

            for &v in &adj[u] {
                deg[v] -= 1;

                if deg[v] == 0 {
                    queue.push_back(v);
                }
            }
        }

        reachable == n
    };

    for _ in 0..t {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();

        let mut adj = vec![vec![]; n];

        for _ in 0..m {
            let u = sc.next::<usize>() - 1;
            let v = sc.next::<usize>() - 1;

            adj[u].push(v);
        }

        if is_dag(&adj) {
            writeln!(writer, "NAO").ok();
        } else {
            writeln!(writer, "SIM").ok();
        }
    }
}
