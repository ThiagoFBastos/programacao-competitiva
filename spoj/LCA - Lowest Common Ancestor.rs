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
   adj: Vec<Vec<usize>>,
   depth: Vec<i32>,
   st: Vec<Vec<usize>>
}

impl LCA {

   fn new(n: usize) -> Self {

      assert_ne!(n, 0);

      let lg = 32 - (n as i32).leading_zeros();

      Self {
         adj: vec![vec![]; n],
         depth: vec![0; n],
         st: vec![vec![0; n]; lg as usize]
      }
   }

   fn dfs(&mut self, u: usize, p: usize) {
      self.st[0][u] = p;

      for i in 1..self.st.len() {
         self.st[i][u] = self.st[i - 1][self.st[i - 1][u]];
      }

      for &v in self.adj[u].clone().iter() {
         if v == p {
            continue;
         }

         self.depth[v] = 1 + self.depth[u];
         self.dfs(v, u);         
      }
   }

   fn build(&mut self, root: usize) {
      self.depth[root] = 0;
      self.dfs(root, root);
   }

   fn add_edge(&mut self, u: usize, v: usize) {
      self.adj[u].push(v);
      self.adj[v].push(u);
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

}

fn main() {
   let mut handle = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let tc = sc.next::<usize>().unwrap();

   for i in 1..=tc {

      let n = sc.next::<usize>().unwrap();

      let mut is_root = vec![true; n];

      let mut lca = LCA::new(n);

      for u in 0..n {
         let m = sc.next::<usize>().unwrap();

         for _ in 0..m {
            let v = sc.next::<usize>().unwrap() - 1;

            lca.add_edge(u, v);
            is_root[v] = false;
         }
      }

      let (root, _) = is_root.iter().enumerate().find(|element| *element.1).unwrap();

      lca.build(root);

      let q = sc.next::<usize>().unwrap();

      writeln!(handle, "Case {}:", i).ok();

      for _ in 0..q {
         let u = sc.next::<usize>().unwrap() - 1;
         let v = sc.next::<usize>().unwrap() - 1;

         let w = lca.query(u, v);

         writeln!(handle, "{}", w + 1).ok();
      }
   }
}
