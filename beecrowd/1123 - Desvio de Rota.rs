#![allow(unused_imports)]
use std::collections::{VecDeque, BinaryHeap};
use std::io::Write;
use std::cmp::Reverse;
use std::iter::Rev;
 
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

struct Graph {
   adj: Vec<Vec<(usize, i32)>>,
   n: usize
}

impl Graph {

   fn new(n: usize) -> Self {

      Self {
         adj: (0..n).map(|_| Vec::new()).collect::<Vec<Vec<(usize, i32)>>>(),
         n: n
      }
   }

   fn add_edge(&mut self, u: usize, v: usize, w: i32) {
      self.adj[u].push((v, w));
      self.adj[v].push((u, w));
   }
}

trait Dijkstra {

   fn min_cost(&mut self, src: usize, stop: usize) -> i32;
}

impl Dijkstra for Graph {

   fn min_cost(&mut self, src: usize, stop: usize) -> i32 {

      let n = self.n;

      let mut cost = (0..n).map(|_| [-1, -1]).collect::<Vec<[i32;2]>>();
      let mut next = vec![-1; n];

      for a in 0..n {
         for &(b, w) in self.adj[a].iter() {
            if a + 1 == b && b < stop {
               next[a] = w;
            }
         }
      }

      let mut pq = BinaryHeap::new();

      pq.push(Reverse((0, 0, src)));

      while !pq.is_empty() {

         let Reverse((ct, t, u)) = pq.pop().unwrap();

         if cost[u][t] != -1 {
            continue;
         }

         cost[u][t] = ct;

         if u < stop - 1 {

            if cost[u + 1][1] == -1 {
               pq.push(Reverse((ct + next[u], 1, u + 1)));
            }
         } else {

            for &(v, w) in self.adj[u].iter() {

               let nt = if v < stop { 1 } else { 0 };

               if cost[v][nt] != -1 {
                  continue;
               }

               pq.push(Reverse((ct + w, nt, v)));
            }
         }
      }

      cost[stop - 1][1]
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   loop {
 
      let n = sc.next::<usize>();
      let m = sc.next::<usize>();
      let c = sc.next::<usize>();
      let k = sc.next::<usize>();

      if n + m + c + k == 0 {
         break;
      }

      let mut graph = Graph::new(n);

      for _ in 0..m {
         let a = sc.next::<usize>();
         let b = sc.next::<usize>();
         let w = sc.next::<i32>();

         graph.add_edge(a, b, w);
      }

      writeln!(handle, "{}", graph.min_cost(k, c)).ok();
   } 
}
