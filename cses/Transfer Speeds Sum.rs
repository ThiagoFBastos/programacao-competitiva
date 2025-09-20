#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};

use crate::data_structures::UnionFind;

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

mod data_structures {

   pub struct UnionFind {
      parent: Vec<usize>,
      rank: Vec<i32>,
      size: Vec<i32>
   }

   impl UnionFind {

      pub fn new(n: usize) -> Self {

         Self {

            parent: (0..n).collect(),
            rank: vec![0; n],
            size: vec![1; n]
         }
      }

      fn find_set(&mut self, u: usize) -> usize {
         if u == self.parent[u] {
            return u;
         }

         self.parent[u] = self.find_set(self.parent[u]);

         return self.parent[u];
      }

      pub fn unite(&mut self, mut u: usize, mut v: usize, weight: i64) -> i64 {

         u = self.find_set(u);
         v = self.find_set(v);

         if self.rank[u] > self.rank[v] {
            std::mem::swap(&mut u, &mut v);
         }

         let combinations = self.size[u] as i64 * self.size[v] as i64 * weight;

         self.parent[u] = v;
         self.size[v] += self.size[u];
         self.rank[v] = if self.rank[u] == self.rank[v] {
            self.rank[v] + 1
         } else {
            self.rank[v]
         };

         combinations
      }
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
   
   let n = sc.next::<usize>().ok().unwrap();

   let mut sum = i64::default();

   let mut uf = UnionFind::new(n);

   let mut edges = (1..n).map(|_| {
      let a = sc.next::<usize>().ok().unwrap() - 1;
      let b = sc.next::<usize>().ok().unwrap() - 1;
      let weight = sc.next::<i64>().ok().unwrap();

      (weight, a, b)
   }).collect::<Vec<_>>();

   edges.sort();
   edges.reverse();

   for &(weight, a, b) in edges.iter() {
      sum += uf.unite(a, b, weight);
   }

   writeln!(handle, "{sum}").ok();
}