#![allow(dead_code)]
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

struct SCCDecomposition {
    adj: Vec<Vec<usize>>,
    low: Vec<Option<usize>>,
    desc: Vec<Option<usize>>,
    scc: Vec<Option<usize>>,
    stack: VecDeque<usize>,
    time: usize,
    count_scc: usize,
}

impl SCCDecomposition {
    fn new(n: usize) -> Self {
        Self {
            adj: vec![vec![]; n],
            low: vec![None; n],
            desc: vec![None; n],
            scc: vec![None; n],
            stack: VecDeque::new(),
            time: 0,
            count_scc: 0,
        }
    }

    fn add_edge(&mut self, u: usize, v: usize) {
        self.adj[u].push(v);
    }

    fn dfs(&mut self, root: usize) {
        self.low[root] = Some(self.time);
        self.desc[root] = Some(self.time);
        self.time += 1;
        self.stack.push_front(root);

        for v in self.adj[root].clone() {
            if self.desc[v].is_none() {
                self.dfs(v);
                self.low[root] = std::cmp::min(self.low[root], self.low[v]);
            } else if self.scc[v].is_none() {
                self.low[root] = std::cmp::min(self.low[root], self.low[v]);
            }
        }

        if self.low[root] != self.desc[root] {
            return;
        }

        while let Some(vertex) = self.stack.pop_front() {
            self.scc[vertex] = Some(self.count_scc);

            if root == vertex {
                break;
            }
        }

        self.count_scc += 1;
    }

    fn decomposition(&mut self) -> Vec<Vec<usize>> {
        let n = self.adj.len();

        for vertex in 0..n {
            if self.desc[vertex].is_none() {
                self.dfs(vertex);
            }
        }

        let mut graph = vec![vec![]; self.count_scc];

        for (vertex, adjacency) in self.adj.iter().enumerate() {
            for &neighbour in adjacency {
                let u = self.scc[vertex].unwrap();
                let v = self.scc[neighbour].unwrap();

                if u != v {
                    graph[u].push(v);
                }
            }
        }

        graph
    }
}

fn solve() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    let n = sc.next::<usize>().unwrap();
    let m = sc.next::<usize>().unwrap();

    let mut scc_decomposition = SCCDecomposition::new(n);

    for _ in 0..m {
        let u = sc.next::<usize>().unwrap() - 1;
        let v = sc.next::<usize>().unwrap() - 1;

        scc_decomposition.add_edge(u, v);
    }

    let graph = scc_decomposition.decomposition();

    let n = graph.len();
    let mut queue = VecDeque::new();
    let mut degree = vec![0; n];

    for adjacency in &graph {
        for &u in adjacency {
            degree[u] += 1;
        }
    }

    for (v, &deg) in degree.iter().enumerate() {
        if deg == 0 {
            queue.push_back(v);
        }
    }

    while queue.len() == 1
    {
        if let Some(v) = queue.pop_front() {
            for &u in &graph[v] {
                degree[u] -= 1;
                if degree[u] == 0 {
                    queue.push_back(u);
                }
            }
        }
    }

    if queue.is_empty() {
        writeln!(writer, "Bolada").ok();
    } else {
        writeln!(writer, "Nao Bolada").ok();
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
