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

struct Trie {
    children: Vec<[Option<usize>; 2]>,
    leaves: Vec<bool>,
    nodes: usize,
}

impl Trie {
    fn new() -> Self {
        Self {
            children: vec![[None, None]],
            leaves: vec![false],
            nodes: 1,
        }
    }

    fn push(&mut self, s: &str) {
        let mut cur = 0;

        for c in s.chars() {
            let bit = c.to_digit(10).unwrap() as usize;

            if let Some(vertex) = self.children[cur][bit] {
                cur = vertex;
            } else {
                self.children[cur][bit] = Some(self.nodes);
                self.children.push([None, None]);
                self.leaves.push(false);
                cur = self.nodes;
                self.nodes += 1
            }
        }

        self.leaves[cur] = true;
    }
}

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    loop {
        let token = sc.next::<usize>();

        if token.is_err() {
            break;
        }

        let n = token.unwrap();
        let m = sc.next::<usize>().unwrap();

        let mut trie1 = Trie::new();
        let mut trie2 = Trie::new();

        for _ in 0..n {
            let str = sc.next::<String>().unwrap();
            trie1.push(&str);
        }

        for _ in 0..m {
            let str = sc.next::<String>().unwrap();
            trie2.push(&str);
        }

        let trie1_nodes = trie1.nodes;
        let trie2_nodes = trie2.nodes;

        let mut vis = vec![vec![false; trie2_nodes]; trie1_nodes];
        let mut queue = VecDeque::new();
        let mut is_possible = false;

        vis[0][0] = true;
        queue.push_back((0, 0));

        while let Some((i, j)) = queue.pop_front() {
            if trie1.leaves[i] && trie2.leaves[j] {
                is_possible = true;
                break;
            } else if trie1.leaves[i] {
                for bit in 0..2 {
                    if let Some(next_i) = trie1.children[0][bit] {
                        if let Some(next_j) = trie2.children[j][bit] {
                            if !vis[next_i][next_j] {
                                vis[next_i][next_j] = true;
                                queue.push_back((next_i, next_j));
                            }
                        }
                    }
                }
            } else if trie2.leaves[j] {
                for bit in 0..2 {
                    if let Some(next_i) = trie1.children[i][bit] {
                        if let Some(next_j) = trie2.children[0][bit] {
                            if !vis[next_i][next_j] {
                                vis[next_i][next_j] = true;
                                queue.push_back((next_i, next_j));
                            }
                        }
                    }
                }
            }

            for bit in 0..2 {
                if let Some(next_i) = trie1.children[i][bit] {
                    if let Some(next_j) = trie2.children[j][bit] {
                        if !vis[next_i][next_j] {
                            vis[next_i][next_j] = true;
                            queue.push_back((next_i, next_j));
                        }
                    }
                }
            }
        }

        if is_possible {
            writeln!(writer, "S").ok();
        } else {
            writeln!(writer, "N").ok();
        }
    }
}
