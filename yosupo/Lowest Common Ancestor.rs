#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};

use crate::data_structures::graphs::LCA;

struct Scanner {
   buffer: VecDeque<String>,
   reader: io::BufReader<io::Stdin>
}

impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new(),
         reader: io::BufReader::new(io::stdin())
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
 
      if self.buffer.is_empty() {
         let mut input = String::new();

         match self.reader.read_line(&mut input) {
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

         if self.buffer.is_empty() {
            self.buffer.push_back("".to_string());
         }
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

mod data_structures {
   
   pub mod graphs {

      #[derive(Clone)]
      pub struct LCA {
         adj: Vec<Vec<(usize, i64)>>, // the adjacency list with weights
         depth: Vec<i32>, // the depth/height of each vertex
         st: Vec<Vec<usize>>, // the sparse table for jumps
         weight: Vec<i64> // the sum of weights from the root to each vertex
      }

      impl LCA {

         /**
          * Create a new instance of LCA data structure
          * @param n the number of nodes
          * @return the new LCA data structure
          */
         pub fn new(n: usize) -> Self {

            assert_ne!(n, 0);

            let lg = 32 - (n as i32).leading_zeros();

            Self {
               adj: vec![vec![]; n],
               depth: vec![0; n],
               st: vec![vec![0; lg as usize]; n],
               weight: vec![0; n]
            }
         }

         /**
          * Do a DFS from the root to the vertexes to calculate some properties
          * @param u the vertex to do the search
          * @param p the parent of vertex u
          */
         fn dfs(&mut self, u: usize, p: usize) {
            self.st[u][0] = p;

            for i in 1..self.st[u].len() {
               self.st[u][i] = self.st[self.st[u][i - 1]][i - 1];
            }

            for &(v, w) in self.adj[u].clone().iter() {
               if v == p {
                  continue;
               }

               self.depth[v] = 1 + self.depth[u];
               self.weight[v] = w + self.weight[u];
               self.dfs(v, u);         
            }
         }

         /**
          * Build the LCA data structure using a vertex as root
          * @param root the root of the tree
          */
         pub fn build(&mut self, root: usize) {
            self.depth[root] = 0;
            self.weight[root] = 0;
            self.dfs(root, root);
         }

         /**
          * Add an undirected edge between u and v with weight w, being that w = 1 if the tree is unweighted
          * @param u a vertex of the edge
          * @param v a vertex of the edge
          * @param w the weight of the edge
          */
         pub fn add_edge(&mut self, u: usize, v: usize, w: i64) {
            self.adj[u].push((v, w));
            self.adj[v].push((u, w));
         }

         /**
          * Find the LCA of two vertexes
          * @param u a vertex of pair to find the lca
          * @param v a vertex of pair to find the lca
          * @return the lca of u and v
          */
         pub fn query(&self, mut u: usize, mut v: usize) -> usize {
            if self.depth[u] > self.depth[v] {
               std::mem::swap(&mut u, &mut v);
            }

            let height = self.depth[v] - self.depth[u];

            if height != 0 {
               let lg = 31 - height.leading_zeros() as usize;
               
               for i in 0..=lg {
                  if (height >> i) & 1 == 1 {
                     v = self.st[v][i];
                  } 
               }
            }

            if u == v {
               return u;
            }

            let lg = 31 - self.depth[u].leading_zeros() as usize;

            for i in (0..=lg).rev() {
               if self.st[u][i] == self.st[v][i] {
                  continue;
               }

               u = self.st[u][i];
               v = self.st[v][i];
            }

            return self.st[u][0];
         }

         /**
          * Calculate the distance between two nodes
          * @param u the vertex of the pair to find the distance
          * @param v the vertex of the pair to find the distance
          * @return the distance between u and v
          */
         pub fn distance(&self, u: usize, v: usize) -> i64 {
            let x = self.query(u, v);
            return self.weight[u] + self.weight[v] - 2 * self.weight[x];
         }
      }
   }
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let mut lca = LCA::new(n);

   for i in 1..n {
      let p = sc.next::<usize>().unwrap();

      lca.add_edge(p, i, 1);
   }

   lca.build(0);

   for _ in 0..q {
      let u = sc.next::<usize>().unwrap();
      let v = sc.next::<usize>().unwrap();

      writeln!(writer, "{}", lca.query(u, v)).ok();
   }
}
