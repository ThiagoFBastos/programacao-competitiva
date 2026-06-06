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
}

fn gcd(mut a: i32, mut b: i32) -> i32 {
    while a % b != 0 {
        let r = a % b;

        a = b;
        b = r;
    }

    b
}

struct Graph {
    adj: Vec<Vec<usize>>,
    weight: Vec<i32>,
    vis: Vec<usize>,
    time: usize,
}

impl Graph {
    fn new(weight: &[i32]) -> Self {
        let n = weight.len();

        Self {
            adj: vec![vec![]; n],
            weight: weight.to_vec(),
            vis: vec![0; n],
            time: 1,
        }
    }

    fn add_edge(&mut self, u: usize, v: usize) {
        self.adj[u].push(v);
        self.adj[v].push(u);
    }

    fn dfs(&mut self, u: usize, g: i32) -> i32 {
        let mut result = self.weight[u];

        self.vis[u] = self.time;

        for v in self.adj[u].clone() {
            if self.vis[v] == self.time || self.weight[v] % g != 0 {
                continue;
            }

            result = gcd(result, self.dfs(v, g));
        }

        result
    }

    fn find_gcd_path(&mut self, u: usize, g: i32) -> i32 {
        let result = self.dfs(u, g);
        result
    }

    fn to_next_time(&mut self) {
        self.time += 1;
    }
}

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    let n = sc.next::<usize>().unwrap();
    let m = sc.next::<usize>().unwrap();

    let c = (0..n)
        .map(|_| sc.next::<i32>().unwrap())
        .collect::<Vec<_>>();

    let maxn = *c.iter().max().unwrap() as usize;

    let mut inv = vec![vec![]; maxn + 1];

    c.iter()
        .enumerate()
        .for_each(|(i, x)| inv[*x as usize].push(i));

    let mut graph = Graph::new(&c);

    for _ in 0..m {
        let u = sc.next::<usize>().unwrap() - 1;
        let v = sc.next::<usize>().unwrap() - 1;

        graph.add_edge(u, v);
    }

    let mut count = 0;

    for i in 1..=maxn {
        'a: for j in (i..=maxn).step_by(i) {
            for &v in &inv[j] {
                if graph.vis[v] != graph.time {
                    let result = graph.find_gcd_path(v, i as i32);

                    if result == i as i32 {
                        count += 1;
                        break 'a;
                    }
                }
            }
        }

        graph.to_next_time();
    }

    writeln!(writer, "{}", count).ok();
}
