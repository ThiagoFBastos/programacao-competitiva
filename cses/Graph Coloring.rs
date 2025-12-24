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
 
      if self.buffer.is_empty() {
         self.buffer.push_back("".to_string());
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let m = sc.next::<usize>().unwrap();

   let mut adj = vec![vec![false; n]; n];

   for _ in 0..m {
      let u = sc.next::<usize>().unwrap() - 1;
      let v = sc.next::<usize>().unwrap() - 1;

      adj[u][v] = true;
      adj[v][u] = true;
   }

   const INF: i32 = 1_000_000_000;

   let mut indset = vec![true; 1 << n];
   let mut dp = vec![INF; 1 << n];
   let mut parent = vec![-1; 1 << n];

   for i in 0..(1 << n) {
      let mut vertex = Vec::new();

      for j in 0..n {
         if (i >> j) & 1 == 1 {
            vertex.push(j);
         }
      }

      for a in vertex.iter() {
         for b in vertex.iter() {
            indset[i] = indset[i] && !adj[*a][*b];
         }
      }
   }

   dp[0] = 0;
   parent[0] = 0;

   for i in 1..(1 << n) {
      let mut subset = i;

      while subset != 0 {

         if indset[subset] {
            let colors = 1 + dp[i ^ subset];

            if dp[i] > colors {
               dp[i] = colors;
               parent[i] = subset as i32;
            }
         }

         subset = (subset - 1) & i;
      }
   }

   let mut subset = (1 << n) - 1;
   let colors = dp[subset];

   writeln!(handle, "{}", colors).ok();

   let mut color = vec![-1; n];

   for i in 1..=colors {
      for j in 0..n {
         let bit = (parent[subset] as usize >> j) & 1;

         if bit == 1 {
            color[j] = i;
         }
      }

      subset ^= parent[subset] as usize;
   }

   for c in color.iter() {
      write!(handle, "{} ", c).ok();
   }

   write!(handle, "\n").ok();
}
