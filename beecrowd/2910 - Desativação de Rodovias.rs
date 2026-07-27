#![allow(dead_code)]
use std::{
    cmp::Reverse,
    collections::BinaryHeap,
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

type Edge = (usize, i32, i32);
type Adj = Vec<Vec<Edge>>;

fn dijkstra(adj: &Adj) -> Vec<i64> {
    let n = adj.len();

    let mut cost = vec![i64::MAX; n];
    let mut pq = BinaryHeap::new();

    cost[0] = 0;
    pq.push(Reverse((0, 0)));

    while let Some(Reverse((cst, u))) = pq.pop() {
        if cst != cost[u] {
            continue;
        }

        for &(v, length, _) in &adj[u] {
            let total_cost = cst + length as i64;

            if cost[v] > total_cost {
                cost[v] = total_cost;
                pq.push(Reverse((total_cost, v)));
            }
        }
    }

    cost
}

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    let n = sc.next::<usize>();
    let m = sc.next::<usize>();

    let mut adj = vec![vec![]; n];

    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let length = sc.next::<i32>();
        let cost = sc.next::<i32>();

        adj[u].push((v, length, cost));
        adj[v].push((u, length, cost));
    }

    let dist = dijkstra(&adj);
    let mut min_in_edge = vec![i32::MAX; n];

    min_in_edge[0] = 0;

    for (u, neighbours) in adj.iter().enumerate() {
        for &(v, length, cost) in neighbours {
            if dist[v] == dist[u] + length as i64 {
                min_in_edge[v] = std::cmp::min(min_in_edge[v], cost);
            }
        }
    }

    let total_repair_cost = min_in_edge.iter().map(|c| *c as i64).sum::<i64>();

    writeln!(writer, "{}", total_repair_cost).ok();
}
