#![allow(unused_imports)]
use std::collections::{HashMap, VecDeque};
use std::io::Write;
 
struct Scanner {
   buffer : VecDeque<String>
}
 
impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new()
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> T {
 
      if self.buffer.is_empty() {
         let mut input = String::new();
         
         std::io::stdin().read_line(&mut input).ok();
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      front.parse::<T>().ok().unwrap()
   }
}

struct Graph {
   adj: Vec<Vec<usize>>,
   low: Vec<i32>,
   time: Vec<i32>,
   scc: Vec<i32>,
   time_id: i32,
   scc_id: i32,
   stack: VecDeque<usize>
}

trait SCC {

   fn new(n: usize) -> Self;

   fn add_edge(&mut self, u: usize, v: usize);

   fn dfs(&mut self, u: usize);

   fn number_of_components(&mut self) -> i32;
}

impl SCC for Graph {

   fn new(n: usize) -> Self {

      let mut adj = Vec::with_capacity(n);

      (0..n).for_each(|_| adj.push(Vec::new()));

      Self {
         adj: adj,
         low: vec![-1; n],
         time: vec![-1; n],
         scc: vec![-1; n],
         time_id: 0,
         scc_id: 0,
         stack: VecDeque::new()
      }
   }

   fn add_edge(&mut self, u: usize, v: usize) {
      self.adj[u].push(v);
   }

   fn dfs(&mut self, u: usize) {
      self.low[u] = self.time_id;
      self.time[u] = self.time_id;
      self.time_id += 1;

      self.stack.push_front(u);

      for &v in self.adj[u].clone().iter() {

         if self.time[v] == -1 {
            self.dfs(v);
            self.low[u] = self.low[u].min(self.low[v]);
         } else if self.scc[v] == -1 {
            self.low[u] = self.low[u].min(self.low[v]);
         }
      }

      if self.low[u] != self.time[u] {
         return;
      }

      loop {

         let &v = self.stack.front().unwrap();

         self.stack.pop_front();

         self.scc[v] = self.scc_id;

         if u == v {
            break;
         }
      }

      self.scc_id += 1;
   }

   fn number_of_components(&mut self) -> i32 {
      let n = self.adj.len();

      (0..n).for_each(|v| if self.time[v] == -1 { self.dfs(v) });

      self.scc_id
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
 
   let t = sc.next::<usize>();

   for _ in 0..t {

      let n = sc.next::<usize>();

      let mut graph = Graph::new(n);

      let grid = (0..n).map(|_| sc.next::<String>().chars().collect::<Vec<char>>()).collect::<Vec<Vec<char>>>();

      for i in 0..n {
         for j in 0..n {
            if grid[i][j] == 'Y' {
               graph.add_edge(i, j);
            }
         }
      }

      writeln!(handle, "{}", graph.number_of_components()).ok();
   }
}
