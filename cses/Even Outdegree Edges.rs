#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::fmt::format;
use std::io::{self, Error, ErrorKind, Write};

struct Scanner {
   buffer: VecDeque<String>
}

impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new()
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
 
      if self.buffer.is_empty() {
         let mut input = String::new();
         
         match std::io::stdin().read_line(&mut input) {
            Ok(0) => {
               return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
            } Ok(_) => {
               
            } Err(e) => {
               return Err(e);
            }
         }
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();
      }
 
      if self.buffer.is_empty() {
         self.buffer.push_back("".to_string());
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

struct EvenOutDegreeEdges {
   adj: Vec<Vec<usize>>,
   usable: Vec<Vec<usize>>,
   edges: Vec<(usize, usize)>,
   in_deg: Vec<i32>,
   time: i32,
   sum_count_edges: usize
}

impl EvenOutDegreeEdges {

   fn new(n: usize) -> Self {

      Self {
         adj: (0..n).map(|_| Vec::new()).collect(),
         usable: (0..n).map(|_| Vec::new()).collect(),
         edges: Vec::new(),
         in_deg: vec![-1; n],
         time: 0,
         sum_count_edges: 0
      }
   }

   fn add_edges(&mut self, u: usize, v: usize) {
      self.adj[u].push(v);
      self.adj[v].push(u);
   }

   fn dfs(&mut self, u: usize, p: usize) -> bool {

      self.sum_count_edges += self.adj[u].len();

      self.in_deg[u] = self.time;
      self.time += 1;

      for v in self.adj[u].clone().iter() {
         let vertex = *v;

         if self.in_deg[vertex] < 0 {
            if !self.dfs(vertex, u) {
               self.usable[u].push(vertex);
            }
         } else if self.in_deg[vertex] > self.in_deg[u] {
            self.usable[u].push(vertex);
         }
      }

      let parity = self.usable[u].len() % 2;

      while self.usable[u].len() > parity {
         let v = self.usable[u].pop().unwrap();
         self.edges.push((u + 1, v + 1));
      }

      if self.usable[u].len() == 1 {
         self.edges.push((u + 1, p + 1));
         self.edges.push((u + 1, *self.usable[u].last().unwrap() + 1));
         return true;
      }

      false
   }

   fn solve(&mut self, write: &mut impl FnMut(&str) -> ()) {
      let n = self.adj.len();

      for i in 0..n {
         if self.in_deg[i] != -1 {
            continue;
         }

         self.sum_count_edges = 0;
         self.dfs(i, i);

         if self.sum_count_edges % 4 != 0 {
            write("IMPOSSIBLE");
            return;
         }
      }

      for (u, v) in self.edges.iter() {
         write(format!("{} {}", u, v).as_str());
      }
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let m = sc.next::<usize>().ok().unwrap();

   let mut solver = EvenOutDegreeEdges::new(n);

   for _ in 0..m {
      let a = sc.next::<usize>().ok().unwrap();
      let b = sc.next::<usize>().ok().unwrap();
      solver.add_edges(a - 1, b - 1);
   }

   let mut write = |s: &str| {
      writeln!(handle, "{}", s).ok();   
   };

   solver.solve(&mut write);
}
