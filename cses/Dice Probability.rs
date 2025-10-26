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

   const MAXN: usize = 101;
   const MAXM: usize = 601;

   let mut dp = [[0.0; MAXM]; MAXN];

   let n = sc.next::<usize>().ok().unwrap();
   let a = sc.next::<usize>().ok().unwrap();
   let b = sc.next::<usize>().ok().unwrap();

   dp[0][0] = 1.0;

   for k in 1..=n {
      let mut s = k - 1;
      let t = 6 * (k - 1);

      while s <= t {
         for i in 1..=6 {
            dp[k][s + i] += dp[k - 1][s] / 6.0;
         }

         s += 1;
      }
   }

   let mut prob = 0.0;

   for k in a..=b {
      prob += dp[n][k];
   }

   writeln!(handle, "{:.6}", prob).ok();
 }
