#![allow(dead_code)]
use std::{
    collections::{BTreeMap, VecDeque},
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

type Graph = Vec<Vec<usize>>;

fn bfs(adj: &Graph) -> Vec<usize> {
    let n = adj.len();

    let mut deg = vec![0; n];
    let mut dist = vec![0; n];
    let mut queue = VecDeque::new();

    for i in 0..n {
        deg[i] = adj[i].len();

        if deg[i] == 1 {
            queue.push_back(i);
        }
    }

    while !queue.is_empty() {
        let src = queue.pop_front().unwrap();

        for &dest in adj[src].iter() {
            deg[dest] -= 1;

            if deg[dest] == 1 {
                dist[dest] = 1 + dist[src];
                queue.push_back(dest);
            }
        }
    }

    dist
}

/**
 * Find the diameter of a given tree
 * @param adj the adjacency list of the tree
 * @return the diameter
 */
fn tree_diameter(adj: &Graph) -> usize {
    assert_ne!(adj.len(), 0);

    let dist = bfs(adj);

    let e = *dist.iter().max().unwrap();
    let count = dist.iter().filter(|&&x| x == e).count();

    2 * e + count - 1
}

/**
 * Find the center of a given tree
 * @param adj the adjacency list of the tree
 * @return the center
 */
fn tree_center(adj: &Graph) -> Vec<usize> {
    assert_ne!(adj.len(), 0);

    let dist = bfs(adj);

    let e = *dist.iter().max().unwrap();

    dist.iter()
        .enumerate()
        .filter(|&x| *x.1 == e)
        .map(|x| x.0)
        .collect::<Vec<_>>()
}

struct Ahu {
    pattern: BTreeMap<Vec<i32>, i32>, // patterns of the vertices
}

impl Default for Ahu {
    fn default() -> Self {
        Self::new()
    }
}

impl Ahu {
    fn new() -> Self {
        Self {
            pattern: BTreeMap::new(),
        }
    }

    fn dfs(&mut self, g: &Graph, u: usize, p: Option<usize>) -> i32 {
        let mut patterns = Vec::new();

        for &v in g[u].iter() {
            if Some(v) != p {
                patterns.push(self.dfs(g, v, Some(u)));
            }
        }

        patterns.sort();

        if !self.pattern.contains_key(&patterns) {
            let id = self.pattern.len() as i32;

            self.pattern.insert(patterns, id);

            return id;
        }

        *self.pattern.get(&patterns).unwrap()
    }

    /**
     * Find a unique pattern of the rooted tree
     */
    fn get_tree_pattern(&mut self, g: &Graph, root: usize) -> i32 {
        assert_ne!(g.len(), 0);
        self.dfs(g, root, None)
    }

    /**
     * @brief Find a unique pattern of the tree
     */
    fn get_tree_canonical_pattern(&mut self, g: &Graph) -> i32 {
        let mut max_pattern = 0;

        if !g.is_empty() {
            for v in tree_center(g) {
                max_pattern = max_pattern.max(self.get_tree_pattern(g, v));
            }
        }

        max_pattern
    }
}

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    while sc.has_next() {
        let n = sc.next::<usize>();

        let mut tree1 = vec![vec![]; n];
        let mut tree2 = vec![vec![]; n];

        for _ in 1..n {
            let u = sc.next::<usize>() - 1;
            let v = sc.next::<usize>() - 1;

            tree1[u].push(v);
            tree1[v].push(u);
        }

        for _ in 1..n {
            let u = sc.next::<usize>() - 1;
            let v = sc.next::<usize>() - 1;

            tree2[u].push(v);
            tree2[v].push(u);
        }

        let mut ahu = Ahu::new();

        if ahu.get_tree_canonical_pattern(&tree1) == ahu.get_tree_canonical_pattern(&tree2) {
            writeln!(writer, "S").ok();
        } else {
            writeln!(writer, "N").ok();
        }
    }
}
