#![allow(dead_code)]
use std::io::{self, Read, Write};

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

struct Solution {
    adj: Vec<Vec<usize>>,
    n: usize,
    dp: Vec<[i64; 3]>,
    modulo: i64,
}

impl Solution {
    fn new(n: usize) -> Self {
        Self {
            adj: vec![vec![]; n],
            n,
            dp: vec![[0; 3]; n],
            modulo: 1_000_000_007,
        }
    }

    fn add_edge(&mut self, u: usize, v: usize) {
        self.adj[u].push(v);
        self.adj[v].push(u);
    }

    fn dfs(&mut self, u: usize, p: Option<usize>) {
        let mut only_adjacency = 1;

        self.dp[u][0] = 1;
        self.dp[u][1] = 1;
        self.dp[u][2] = 1;

        for v in self.adj[u].clone() {
            if Some(v) == p {
                continue;
            }

            self.dfs(v, Some(u));

            self.dp[u][0] = self.dp[u][0] * self.dp[v][2] % self.modulo;
            self.dp[u][1] =
                self.dp[u][1] * (self.dp[v][0] + self.dp[v][1] + self.dp[v][2]) % self.modulo;
            self.dp[u][2] = self.dp[u][2] * (self.dp[v][1] + self.dp[v][2]) % self.modulo;
            only_adjacency = only_adjacency * self.dp[v][2] % self.modulo;
        }

        self.dp[u][2] = (self.dp[u][2] - only_adjacency + self.modulo) % self.modulo;
    }

    fn find_number_of_ways(&mut self) -> i64 {
        self.dfs(0, None);

        (self.dp[0][1] + self.dp[0][2]) % self.modulo
    }
}

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    while sc.has_next() {
        let n = sc.next::<usize>();

        let mut sol = Solution::new(n);

        for _ in 1..n {
            let u = sc.next::<usize>();
            let v = sc.next::<usize>();

            sol.add_edge(u - 1, v - 1);
        }

        writeln!(writer, "{}", sol.find_number_of_ways()).ok();
    }
}
