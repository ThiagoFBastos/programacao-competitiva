#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
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

struct DisjointSet {
   parent: Vec<usize>,
   rank: Vec<u32>
}

impl DisjointSet {

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

   fn unite(&mut self, mut u: usize, mut v: usize) {

      u = self.find_set(u);
      v = self.find_set(v);

      if u == v{
         return;
      } else if self.rank[u] > self.rank[v] {
         std::mem::swap(&mut u, &mut v);
      }

      self.parent[u] = v;
      self.rank[v] = if self.rank[u] == self.rank[v] { self.rank[v] + 1 } else { self.rank[v] };
   }

   fn same(& mut self, u: usize, v: usize) -> bool {
      return self.find_set(u) == self.find_set(v);
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();


   let n = sc.next::<usize>().ok().unwrap();
   let q = sc.next::<usize>().ok().unwrap();

   let mut uf = DisjointSet::new(n);

   for _ in 0..q {
      let t = sc.next::<u8>().ok().unwrap();
      let u = sc.next::<usize>().ok().unwrap();
      let v = sc.next::<usize>().ok().unwrap();

      if t == 0 {
         uf.unite(u, v);
      } else if uf.same(u, v) {
         writeln!(handle, "1").ok();
      } else {
         writeln!(handle, "0").ok();
      }
   }
 }
