#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, HashMap};
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
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

struct UnionFind {
   parent: Vec<usize>,
   rank: Vec<u32>
}

impl UnionFind {

   fn new(n: usize) -> Self {

      Self {
         parent: (0..n).collect(),
         rank: vec![0; n]
      }
   }

   fn find_set(&mut self, u: usize) -> usize {

      if u == self.parent[u] {
         return u;
      }

      self.parent[u] = self.find_set(self.parent[u]);

      return self.parent[u];
   }

   fn is_same(&mut self, u: usize, v: usize) -> bool {
      self.find_set(u) == self.find_set(v)
   }

   fn unite(&mut self, mut u: usize, mut v: usize) {
      u = self.find_set(u);
      v = self.find_set(v);

      if u == v {
         return;
      } else if self.rank[u] > self.rank[v] {
         std::mem::swap(&mut u, &mut v);
      }

      self.parent[u] = v;
      self.rank[v] = if self.rank[u] == self.rank[v] { self.rank[v] + 1 } else { self.rank[v] };
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let m = sc.next::<usize>().ok().unwrap();

   let mut uf = UnionFind::new(n);

   let mut edges = Vec::with_capacity(m);

   let mut total_weight = 0;

   for i in 0..m {
      let a = sc.next::<usize>().ok().unwrap();
      let b = sc.next::<usize>().ok().unwrap();
      let weight = sc.next::<i32>().ok().unwrap();

      edges.push((a, b, weight, i));
   }

   edges.sort_by_key(|e| e.2);

   let mut edge_pos = Vec::new();

   for &(a, b, weight, pos) in edges.iter() {

      if !uf.is_same(a, b) {
         uf.unite(a, b);
         total_weight += weight as i64;
         edge_pos.push(pos);
      }
   }

   writeln!(handle, "{total_weight}").ok();

   for pos in edge_pos.iter() {
      write!(handle, "{} ", pos).ok();
   }

   write!(handle, "\n").ok();
 }
