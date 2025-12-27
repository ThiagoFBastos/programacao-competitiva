#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};

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

   fn ignore(&mut self) {
      if !self.buffer.is_empty() {
         self.buffer.pop_front();
      }
   }
}

const MOD: i32 = 998244353;

struct DisjointSet {
   parent: Vec<usize>,
   rank: Vec<u32>,
   up: Vec<i32>
}

impl DisjointSet {

   fn new(n: usize) -> Self {

      Self {
         parent: (0..n).collect(),
         rank: vec![0; n],
         up: vec![0; n]
      }
   }

   fn find_set(&self, mut u: usize) -> (usize, i32) {
      let mut weight = 0;

      while u != self.parent[u] {
         weight += self.up[u];
         if weight >= MOD {
            weight -= MOD;
         }
         u = self.parent[u];
      }

      (u, weight)
   }

   fn same(&self, u: usize, v: usize) -> bool {
      let (a, _) = self.find_set(u);
      let (b, _) = self.find_set(v);

      return a == b;
   }

   fn unite(&mut self, u: usize, v: usize, mut weight: i32) -> bool {
      let (mut a, mut wa) = self.find_set(u);
      let (mut b, mut wb) = self.find_set(v);

      wa *= -1;

      if a == b {
         return false;
      } else if self.rank[a] > self.rank[b] {
         weight *= -1;
         wa *= -1;
         wb *= -1;
         std::mem::swap(&mut a, &mut b);
         std::mem::swap(&mut wa, &mut wb);
      }

      self.parent[a] = b;
      self.up[a] = (((wa + wb) % MOD + weight) % MOD + MOD) % MOD;
      self.rank[b] = if self.rank[a] == self.rank[b] { 1 + self.rank[b] } else { self.rank[b] };

      return true;
   }

   fn height(&self, mut u: usize) -> i32 {
      let mut h = 0;

      while u != self.parent[u] {
         u = self.parent[u];
         h += 1;
      }

      return h;
   }

   fn distance(&self, mut u: usize, mut v: usize) -> i32 {
      let mut hu = self.height(u);
      let mut hv = self.height(v);
      let mut distance = 0;

      while u != v {
         if hu > hv {
            distance += self.up[u];

            if distance >= MOD {
               distance -= MOD;
            }

            hu -= 1;
            u = self.parent[u];
         } else if hu < hv {
            distance -= self.up[v];

            if distance < 0 {
               distance += MOD;
            }

            hv -= 1;
            v = self.parent[v];
         } else {
            distance += self.up[u];

            if distance >= MOD {
               distance -= MOD;
            }

            hu -= 1;
            u = self.parent[u];

            distance -= self.up[v];

            if distance < 0 {
               distance += MOD;
            }

            hv -= 1;
            v = self.parent[v];
         }
      }

      return distance;
   }
}

fn main() {
   let mut handle = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let mut uf = DisjointSet::new(n);

   for _ in 0..q {

      let t = sc.next::<i32>().unwrap();
      let u = sc.next::<usize>().unwrap();
      let v = sc.next::<usize>().unwrap();

      if t == 0 {
         let x = sc.next::<i32>().unwrap();

         if uf.unite(u, v, x) {
            writeln!(handle, "1").ok();
         } else {
            let d = uf.distance(u, v);
            writeln!(handle, "{}", if d == x { 1 } else { 0 }).ok();
         }

      } else {
         if uf.same(u, v) {
            writeln!(handle, "{}", uf.distance(u, v)).ok();
         } else {
            writeln!(handle, "-1").ok();
         }
      }
   }
}
