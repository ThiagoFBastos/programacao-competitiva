#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::VecDeque;
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

#[derive(Clone)]
struct DisjointSet {
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
    fn unite(&mut self, mut u: usize, mut v: usize) {
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
    fn same(&mut self, u: usize, v: usize) -> bool {
        self.find_set(u) == self.find_set(v)
    }
}

fn minimum_spanning_tree(edges: &[(usize, usize, i32)], n: usize) -> Vec<Vec<(usize, i32)>> {
    let mut graph = vec![vec![]; n];
    let mut uf = DisjointSet::new(n);
    let mut graph_edges = edges.to_vec();

    graph_edges.sort_by_key(|e| e.2);

    for (u, v, w) in graph_edges {
        if !uf.same(u, v) {
            uf.unite(u, v);
            graph[u].push((v, w));
            graph[v].push((u, w));
        }
    }

    graph
}

struct BinaryLifting {
    parent: Vec<Vec<usize>>,
    max_weight: Vec<Vec<i32>>,
    depth: Vec<usize>,
    graph: Vec<Vec<(usize, i32)>>,
}

impl BinaryLifting {
    fn new(graph: Vec<Vec<(usize, i32)>>) -> Self {
        let n = graph.len();
        let log = 32 - (n as u32).leading_zeros() as usize;

        let parent = vec![vec![0; n]; log];
        let max_weight = vec![vec![0; n]; log];
        let depth = vec![0; n];

        Self {
            parent,
            max_weight,
            depth,
            graph,
        }
    }

    fn dfs(&mut self, u: usize, p: usize, w: i32) {
        self.parent[0][u] = p;
        self.max_weight[0][u] = w;

        for (v, weight) in self.graph[u].clone() {
            if v != p {
                self.depth[v] = self.depth[u] + 1;
                self.dfs(v, u, weight);
            }
        }
    }

    fn build(&mut self) {
        let n = self.graph.len();
        let log = 32 - (n as u32).leading_zeros() as usize;

        self.dfs(0, 0, 0);

        for j in 1..log {
            for i in 0..n {
                self.parent[j][i] = self.parent[j - 1][self.parent[j - 1][i]];
                self.max_weight[j][i] = std::cmp::max(
                    self.max_weight[j - 1][i],
                    self.max_weight[j - 1][self.parent[j - 1][i]],
                );
            }
        }
    }

    fn query(&self, mut u: usize, mut v: usize) -> i32 {
        if self.depth[u] < self.depth[v] {
            std::mem::swap(&mut u, &mut v);
        }

        let log = 32 - (self.graph.len() as u32).leading_zeros() as usize;
        let mut max_edge = 0;
        let diff = self.depth[u] - self.depth[v];

        for j in (0..log).rev() {
            if diff & (1 << j) != 0 {
                max_edge = std::cmp::max(max_edge, self.max_weight[j][u]);
                u = self.parent[j][u];
            }
        }

        if u == v {
            return max_edge;
        }

        for j in (0..log).rev() {
            if self.parent[j][u] != self.parent[j][v] {
                max_edge = std::cmp::max(max_edge, self.max_weight[j][u]);
                max_edge = std::cmp::max(max_edge, self.max_weight[j][v]);
                u = self.parent[j][u];
                v = self.parent[j][v];
            }
        }

        max_edge = std::cmp::max(max_edge, self.max_weight[0][u]);
        max_edge = std::cmp::max(max_edge, self.max_weight[0][v]);
        max_edge
    }
}

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    let n = sc.next::<usize>().unwrap();
    let m = sc.next::<usize>().unwrap();

    let mut edges = Vec::with_capacity(m);

    for _ in 0..m {
        let u = sc.next::<usize>().unwrap();
        let v = sc.next::<usize>().unwrap();
        let w = sc.next::<i32>().unwrap();

        edges.push((u, v, w));
    }

    let graph = minimum_spanning_tree(&edges, n);

    let mut bl = BinaryLifting::new(graph);

    bl.build();

    let q = sc.next::<usize>().unwrap();

    for _ in 0..q {
        let u = sc.next::<usize>().unwrap();
        let v = sc.next::<usize>().unwrap();

        writeln!(writer, "{}", bl.query(u, v)).unwrap();
    }
}
