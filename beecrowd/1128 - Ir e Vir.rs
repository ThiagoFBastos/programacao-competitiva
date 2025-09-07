#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::Write;

use crate::algorithms::{Graph, SCC};
 
struct Scanner {
   buffer: VecDeque<String>
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

mod algorithms {
    use std::collections::VecDeque;

   pub struct Graph {
      adj: Vec<Vec<usize>>,
      low: Vec<i32>,
      time: Vec<i32>,
      scc: Vec<i32>,
      time_count: i32,
      pub scc_count: i32,
      pub number_of_components: i32,
      stack: VecDeque<usize>
   }

   impl Graph {

      pub fn new(n: usize) -> Self {

         Self {

            adj: (0..n).map(|_| Vec::new()).collect::<Vec<Vec<usize>>>(),
            low: vec![-1; n],
            time: vec![-1; n],
            scc: vec![-1; n],
            time_count: 0,
            scc_count: 0,
            number_of_components: 0,
            stack: VecDeque::new()
         }
      }

      pub fn add_edge(&mut self, u: usize, v: usize) {
         self.adj[u].push(v);
      }
   }

   pub trait SCC {

      fn dfs(&mut self, u: usize);

      fn find_strongly_connected_components(&mut self);
   }

   impl SCC for Graph {

      fn dfs(&mut self, u: usize) {
         self.low[u] = self.time_count;
         self.time[u] = self.time_count;

         self.time_count += 1;

         self.stack.push_front(u);

         for &v in self.adj[u].clone().iter() {

            if self.time[v] == -1 {
               self.dfs(v);
               self.low[u] = self.low[u].min(self.low[v]);
            } else if self.scc[v] == -1 {
               self.low[u] = self.low[u].min(self.low[v]);
            }
         }

         if self.time[u] == self.low[u] {

            loop {

               let v = self.stack.pop_front().unwrap();

               self.scc[v] = self.scc_count;

               if u == v {
                  break;
               }
            }

            self.scc_count += 1;
         }
      }

      fn find_strongly_connected_components(&mut self) {
         let n = self.adj.len();

         (0..n).for_each(|v|

            if self.time[v] == -1 {
               self.dfs(v);
               self.number_of_components += 1;
            }
         );
      }
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   loop {

      let n = sc.next::<usize>();
      let m = sc.next::<usize>();

      if n + m == 0 {
         break;
      }

      let mut graph = Graph::new(n);

      for _ in 0..m {

         let v = sc.next::<usize>() - 1;
         let w = sc.next::<usize>() - 1;
         let p = sc.next::<u8>();

         if p == 1 {
            graph.add_edge(v, w);
         } else {
            graph.add_edge(v, w);
            graph.add_edge(w, v);
         }
      }

      graph.find_strongly_connected_components();

      if graph.number_of_components > 1 || graph.scc_count > 1 {
         writeln!(handle, "0").ok();
      } else {
         writeln!(handle, "1").ok();
      }
   }
}
