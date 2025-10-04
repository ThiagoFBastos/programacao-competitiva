#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, HashMap};
use std::io::{self, Error, ErrorKind, Write};

use crate::graph_algorithms::Graph;

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
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

mod graph_algorithms {
   use std::collections::VecDeque;

   pub struct Graph {
      adj: Vec<Vec<usize>>,
      time: Vec<Option<u32>>,
      low: Vec<Option<u32>>,
      id: Vec<Option<u32>>,
      stack: VecDeque<usize>,
      time_counter: u32,
      id_counter: u32
   }

   impl Graph {

      pub fn new(n: usize) -> Self {

         Self {
            adj: (0..n).map(|_| Vec::new()).collect(),
            time: vec![None; n],
            low: vec![None; n],
            id: vec![None; n],
            stack: VecDeque::new(),
            time_counter: 0,
            id_counter: 0
         }
      }

      pub fn add_edge(&mut self, u: usize, v: usize) {
         self.adj[u].push(v);
      }

      fn dfs(&mut self, u: usize) {
         self.time[u] = Some(self.time_counter);
         self.low[u] = Some(self.time_counter);
         self.stack.push_front(u);
         self.time_counter += 1;

         for &v in self.adj[u].clone().iter() {
            let before = self.time[v];

            if self.time[v].is_none() {
               self.dfs(v);
            }
            
            if before.is_none() || self.id[v].is_none() {
               if self.low[u].unwrap() > self.low[v].unwrap() {
                  self.low[u] = self.low[v];
               }
            }
         }

         if self.low[u] != self.time[u] {
            return;
         }

         loop {
            let v = self.stack.pop_front().unwrap();

            self.id[v] = Some(self.id_counter);

            if u == v {
               break;
            }
         }

         self.id_counter += 1;
      }

      pub fn decompose(&mut self) -> Vec<Vec<usize>> {
         let n = self.adj.len();

         for u in 0..n {
            if self.time[u].is_none() {
               self.dfs(u);
            }
         }

         let mut vertex = (0..n).collect::<Vec<_>>();

         vertex.sort_by_key(|v| self.id[*v]);
         vertex.reverse();

         let mut scc = Vec::new();

         scc.push(vec![vertex[0]]);

         for i in 1..n {
            let u = vertex[i - 1];
            let v = vertex[i];

            if self.id[u] != self.id[v] {
               scc.push(Vec::new());
            }

            let m = scc.len();
            
            scc[m - 1].push(v);
         }

         return scc;
      }
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let m = sc.next::<usize>().ok().unwrap();

   let mut graph = Graph::new(n);

   for _ in 0..m {
      let a = sc.next::<usize>().ok().unwrap();
      let b = sc.next::<usize>().ok().unwrap();

      graph.add_edge(a, b);
   }

   let sccs = graph.decompose();

   writeln!(handle, "{}", sccs.len()).ok();

   for scc in sccs.iter() {
      write!(handle, "{}", scc.len()).ok();

      for v in scc.iter() {
         write!(handle, " {}", v).ok();
      }

      write!(handle, "\n").ok();
   }
 }
