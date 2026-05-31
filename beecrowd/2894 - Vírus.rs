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

struct Bridges {
    graph: Vec<Vec<(usize, usize)>>,
    low: Vec<usize>,
    disc: Vec<usize>,
    size: Vec<usize>,
    time: usize,
    egdges: usize,
    bridges: Vec<(usize, usize)>,
}

impl Bridges {
    fn new(n: usize) -> Self {
        Self {
            graph: vec![vec![]; n],
            low: vec![0; n],
            disc: vec![0; n],
            size: vec![0; n],
            time: 0,
            egdges: 0,
            bridges: vec![],
        }
    }

    fn add_edge(&mut self, u: usize, v: usize) {
        self.graph[u].push((v, self.egdges));
        self.graph[v].push((u, self.egdges));
        self.egdges += 1;
    }

    fn dfs(&mut self, u: usize, parent: Option<(usize, usize)>) {
        self.time += 1;
        self.low[u] = self.time;
        self.disc[u] = self.time;
        self.size[u] = 1;

        for (v, e) in self.graph[u].clone() {
            if self.disc[v] == 0 {
                self.dfs(v, Some((u, e)));
                self.size[u] += self.size[v];
                self.low[u] = std::cmp::min(self.low[u], self.low[v]);

                if self.low[v] > self.disc[u] {
                    self.bridges.push((u, v));
                }
            } else if Some((v, e)) != parent {
                self.low[u] = std::cmp::min(self.low[u], self.disc[v]);
            }
        }
    }

    fn find_bridges(&mut self, root: usize) {
        self.dfs(root, None);
    }
}

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    let t = sc.next::<usize>().unwrap();

    for _ in 0..t {
        let n = sc.next::<usize>().unwrap();
        let m = sc.next::<usize>().unwrap();
        let c = sc.next::<usize>().unwrap() - 1;

        let mut bridges = Bridges::new(n);

        for _ in 0..m {
            let u = sc.next::<usize>().unwrap() - 1;
            let v = sc.next::<usize>().unwrap() - 1;

            bridges.add_edge(u, v);
        }

        bridges.find_bridges(c);

        let mut max_number_of_cities = 0;

        for (_, v) in bridges.bridges.iter() {
            max_number_of_cities = std::cmp::max(max_number_of_cities, bridges.size[*v]);
        }

        writeln!(writer, "{}", max_number_of_cities).ok();
    }
}
