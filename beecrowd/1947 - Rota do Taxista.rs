#![allow(dead_code)]
use std::{
    cmp::Reverse,
    collections::BinaryHeap,
    io::{self, Read, Write},
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

fn dijkstra(n: usize, adj: &[Vec<(usize, i32)>], src: usize, dest: usize) -> i32 {
    let mut dist = vec![i32::MAX; n];
    let mut pq = BinaryHeap::new();

    dist[src] = 0;
    pq.push(Reverse((0, src)));

    while let Some(Reverse((cost, v))) = pq.pop() {
        if cost != dist[v] {
            continue;
        } else if v == dest {
            return cost;
        }

        for &(u, w) in &adj[v] {
            let total_cost = cost + w;

            if dist[u] <= total_cost {
                continue;
            }

            dist[u] = total_cost;
            pq.push(Reverse((total_cost, u)));
        }
    }

    panic!("not found");
}

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    let n = sc.next::<usize>();
    let m = sc.next::<usize>();
    let k = sc.next::<usize>();

    let mut adj = vec![vec![]; n];

    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<i32>();

        adj[u].push((v, w));
        adj[v].push((u, w));
    }

    let mut travels = Vec::with_capacity(k + 1);

    for _ in 0..k {
        let src = sc.next::<usize>() - 1;
        let dest = sc.next::<usize>() - 1;
        travels.push((src, dest));
    }

    travels.push((0, 0));

    let mut pairwise_dist = vec![vec![0; k + 1]; k + 1];

    for (i, &pairfrom) in travels.iter().enumerate() {
        let (src1, dest1) = pairfrom;

        pairwise_dist[i][i] = dijkstra(n, &adj, src1, dest1);

        for (j, &pairto) in travels.iter().enumerate() {
            let (src2, _) = pairto;

            if i != j {
                pairwise_dist[i][j] = dijkstra(n, &adj, dest1, src2);
            }
        }
    }

    const INF: i32 = 1_000_000_000;
    let mut dp = vec![vec![INF; k]; 1 << k];

    for i in 0..k {
        dp[1 << i][i] = pairwise_dist[k][i] + pairwise_dist[i][i];
    }

    for i in 0..(1 << k) {
        for l in 0..k {
            if i & (1 << l) == 0 {
                continue;
            }

            for j in 0..k {
                if i & (1 << j) == 0 {
                    continue;
                }

                dp[i][j] = std::cmp::min(
                    dp[i ^ (1 << j)][l] + pairwise_dist[l][j] + pairwise_dist[j][j],
                    dp[i][j],
                );
            }
        }
    }

    let mut min_travel_cost = INF;

    for (i, _) in pairwise_dist.iter().enumerate().take(k) {
        min_travel_cost = std::cmp::min(min_travel_cost, dp[(1 << k) - 1][i] + pairwise_dist[i][k]);
    }

    writeln!(writer, "{}", min_travel_cost).ok();
}
