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

struct LCA {
   adj: Vec<Vec<(usize, i64)>>,
   depth: Vec<i32>,
   st: Vec<Vec<usize>>,
   weight: Vec<i64>
}

impl LCA {

   fn new(n: usize) -> Self {

      assert_ne!(n, 0);

      let lg = 32 - (n as i32).leading_zeros();

      Self {
         adj: vec![vec![]; n],
         depth: vec![0; n],
         st: vec![vec![0; n]; lg as usize],
         weight: vec![0; n]
      }
   }

   fn dfs(&mut self, u: usize, p: usize) {
      self.st[0][u] = p;

      for i in 1..self.st.len() {
         self.st[i][u] = self.st[i - 1][self.st[i - 1][u]];
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

   fn build(&mut self, root: usize) {
      self.depth[root] = 0;
      self.weight[root] = 0;
      self.dfs(root, root);
   }

   fn add_edge(&mut self, u: usize, v: usize, w: i64) {
      self.adj[u].push((v, w));
      self.adj[v].push((u, w));
   }

   fn query(&self, mut u: usize, mut v: usize) -> usize {
      if self.depth[u] > self.depth[v] {
         std::mem::swap(&mut u, &mut v);
      }

      let height = self.depth[v] - self.depth[u];

      if height != 0 {
         let lg = 31 - height.leading_zeros() as usize;
         
         for i in 0..=lg {
            if (height >> i) & 1 == 1 {
               v = self.st[i][v];
            } 
         }
      }

      if u == v {
         return u;
      }

      let lg = 31 - self.depth[u].leading_zeros() as usize;

      for i in (0..=lg).rev() {
         if self.st[i][u] == self.st[i][v] {
            continue;
         }

         u = self.st[i][u];
         v = self.st[i][v];
      }

      return self.st[0][u];
   }

   fn distance(&self, u: usize, v: usize) -> i64 {
      let x = self.query(u, v);
      return self.weight[u] + self.weight[v] - 2 * self.weight[x];
   }

}

fn main() {
   let mut handle = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   loop {

      let n = sc.next::<usize>().unwrap();

      if n == 0 {
         break;
      }

      let mut lca = LCA::new(n);

      for u in 1..n {
         let v = sc.next::<usize>().unwrap();
         let w = sc.next::<i64>().unwrap();

         lca.add_edge(u, v, w);
      }

      lca.build(0);

      let q = sc.next::<usize>().unwrap();

      for i in 0..q {
         let u = sc.next::<usize>().unwrap();
         let v = sc.next::<usize>().unwrap();

         let dist = lca.distance(u, v);

         if i > 0 {
            write!(handle, " ").ok();
         }

         write!(handle, "{}", dist).ok();
      }

      write!(handle, "\n").ok();
   }
}
