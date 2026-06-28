#![allow(dead_code)]
use std::{
    collections::BTreeMap,
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

    fn next<T: std::str::FromStr>(&mut self) -> T {
        while self.index < self.buffer.len() && self.buffer[self.index].is_ascii_whitespace() {
            self.index += 1;
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

#[derive(Clone)]
pub struct DisjointSet {
    parent: Vec<usize>, // the parent of each vertex
    rank: Vec<u32>,     // the rank of the disjoint set
}

impl DisjointSet {
    /**
     * create a new instance of DisjointSet
     * @param n number of vertexes
     * @return a DisjointSet
     */
    pub fn new(n: usize) -> Self {
        Self {
            parent: (0..n).collect(),
            rank: vec![0; n],
        }
    }

    /**
     * find the root of disjoint set that u belongs
     * @param u a vertex of the disjoint set that you want to find the root
     * @return the root of disjoint set
     */
    pub fn find_set(&mut self, u: usize) -> usize {
        if u == self.parent[u] {
            return u;
        }

        self.parent[u] = self.find_set(self.parent[u]);

        self.parent[u]
    }

    /**
     * join the connected components that u and v belongs
     * @param u a vertex of one connected component
     * @param v a vertex of other connected component
     */
    pub fn unite(&mut self, mut u: usize, mut v: usize) {
        u = self.find_set(u);
        v = self.find_set(v);

        if u == v {
            return;
        } else if self.rank[u] > self.rank[v] {
            std::mem::swap(&mut u, &mut v);
        }

        self.parent[u] = v;
        self.rank[v] = if self.rank[u] == self.rank[v] {
            self.rank[v] + 1
        } else {
            self.rank[v]
        };
    }

    /**
     * Return if two vertexes belongs to the same connected component
     * @param u a vertex of one connected component
     * @param v a vertex of one connected component
     * @return true if u and v belongs to the same connected component and false otherwise
     */
    pub fn same(&mut self, u: usize, v: usize) -> bool {
        self.find_set(u) == self.find_set(v)
    }
}

#[derive(Clone)]
struct BinaryLifting {
    up: Vec<Vec<usize>>,
    max_cost: Vec<Vec<i32>>,
    adj: Vec<Vec<(usize, i32)>>,
    depth: Vec<usize>,
    n: usize,
    m: usize,
}

impl BinaryLifting {
    fn new(n: usize) -> Self {
        let m = 32 - (n as i32).leading_zeros() as usize;

        Self {
            up: vec![vec![0; n]; m],
            max_cost: vec![vec![i32::MIN; n]; m],
            adj: vec![vec![]; n],
            depth: vec![0; n],
            n,
            m,
        }
    }

    fn add_edge(&mut self, u: usize, v: usize, w: i32) {
        self.adj[u].push((v, w));
        self.adj[v].push((u, w));
    }

    fn dfs(&mut self, root: usize, parent: Option<(usize, i32)>) {
        if let Some((p, w)) = parent {
            self.up[0][root] = p;
            self.max_cost[0][root] = w;
        } else {
            self.up[0][root] = root;
        }

        for i in 1..self.m {
            self.up[i][root] = self.up[i - 1][self.up[i - 1][root]];
            self.max_cost[i][root] = std::cmp::max(
                self.max_cost[i - 1][root],
                self.max_cost[i - 1][self.up[i - 1][root]],
            );
        }

        for (u, w) in self.adj[root].clone() {
            if Some((u, w)) != parent {
                self.depth[u] = self.depth[root] + 1;
                self.dfs(u, Some((root, w)));
            }
        }
    }

    fn build_tree(&mut self) {
        self.dfs(0, None);
    }

    fn query(&self, mut u: usize, mut v: usize) -> i32 {
        if self.depth[u] > self.depth[v] {
            std::mem::swap(&mut u, &mut v);
        }

        let diff = self.depth[v] - self.depth[u];
        let mut max_edge_cost = i32::MIN;

        if diff > 0 {
            for i in 0..self.m {
                if diff & (1 << i) != 0 {
                    max_edge_cost = std::cmp::max(max_edge_cost, self.max_cost[i][v]);
                    v = self.up[i][v];
                }
            }
        }

        if u == v {
            return max_edge_cost;
        }

        for i in (0..self.m).rev() {
            if self.up[i][u] == self.up[i][v] {
                continue;
            }

            max_edge_cost = std::cmp::max(max_edge_cost, self.max_cost[i][u]);
            max_edge_cost = std::cmp::max(max_edge_cost, self.max_cost[i][v]);

            u = self.up[i][u];
            v = self.up[i][v];
        }

        max_edge_cost = std::cmp::max(max_edge_cost, self.max_cost[0][u]);
        max_edge_cost = std::cmp::max(max_edge_cost, self.max_cost[0][v]);

        max_edge_cost
    }
}

fn solve() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    let n = sc.next::<usize>();
    let m = sc.next::<usize>();

    let mut edges = Vec::with_capacity(m);

    for _ in 0..m {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;
        let w = sc.next::<i32>();

        edges.push((u, v, w));
    }

    edges.sort_by_key(|e| e.2);

    let mut uf = DisjointSet::new(n);
    let mut mst = BTreeMap::new();
    let mut cost = 0;
    let mut lifting = BinaryLifting::new(n);

    for &(u, v, w) in &edges {
        if !uf.same(u, v) {
            uf.unite(u, v);
            lifting.add_edge(u, v, w);
            mst.insert((u, v), w);
            cost += w;
        }
    }

    lifting.build_tree();

    let edges = edges
        .iter()
        .map(|&(u, v, w)| ((u, v), w))
        .collect::<BTreeMap<_, _>>();

    let q = sc.next::<usize>();

    for _ in 0..q {
        let u = sc.next::<usize>() - 1;
        let v = sc.next::<usize>() - 1;

        if mst.contains_key(&(u, v)) {
            writeln!(writer, "{}", cost).ok();
        } else {
            let max_weight = lifting.query(u, v);
            let target_edge_weight = *edges.get(&(u, v)).unwrap();

            writeln!(writer, "{}", cost - max_weight + target_edge_weight).ok();
        }
    }
}

fn main() {
    std::thread::Builder::new()
        .stack_size(64 * 1024 * 1024)
        .spawn(|| {
            solve();
        })
        .unwrap()
        .join()
        .unwrap();
}
