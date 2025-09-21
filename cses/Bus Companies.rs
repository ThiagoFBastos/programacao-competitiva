#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};

use crate::graphs_algorithms::{Graph, MinPathCost};

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
               return Err(Error::new(ErrorKind::UnexpectedEof, "End Of Line"));
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

mod graphs_algorithms {
    use std::{cmp::Reverse, collections::BinaryHeap};

   pub struct Graph {
      adj: Vec<Vec<(usize, i64)>>,
      n: usize
   }

   impl Graph {

      pub fn new(n: usize) -> Self {
         Self {
            adj: (0..n).map(|_| Vec::new()).collect(),
            n: n
         }
      }

      pub fn add_edge(&mut self, u: usize, v: usize, weight: i64) {
         self.adj[u].push((v, weight));
      }
   }

   pub trait MinPathCost {
      fn dijkstra(&self) -> Vec<i64>;
   }

   impl MinPathCost for Graph {

      fn dijkstra(&self) -> Vec<i64> {
         let n = self.n;

         let mut cost = vec![-1; n];
         let mut pq = BinaryHeap::new();

         pq.push(Reverse((0, 0)));

         while !pq.is_empty() {

            let Reverse((c, w)) = pq.pop().unwrap();

            if cost[w] != -1 {
               continue;
            }

            cost[w] = c;

            for &(v, x) in self.adj[w].iter() {

               if cost[v] != -1 {
                  continue;
               }

               pq.push(Reverse((x + c, v)));
            }
         }

         cost
      }
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
   
   let n = sc.next::<usize>().ok().unwrap();
   let m = sc.next::<usize>().ok().unwrap();

   let ticket = (0..m).map(|_| sc.next::<i64>().ok().unwrap()).collect::<Vec<_>>();

   let mut graph = Graph::new(n + m);

   for i in 0..m {

      let cities = sc.next::<usize>().ok().unwrap();

      for _  in 0..cities {

         let city = sc.next::<usize>().ok().unwrap() - 1;

         graph.add_edge(city, n + i, ticket[i]);
         graph.add_edge(n + i, city, 0);
      }
   }

   let mut cost = graph.dijkstra();

   cost.drain(n..(n + m));

   for value in cost.iter() {
      write!(handle, "{value} ").ok();
   }

   writeln!(handle, "").ok();
}