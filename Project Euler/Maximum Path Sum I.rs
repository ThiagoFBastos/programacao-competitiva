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

   let mut sc  = Scanner::new();

   const INF: i32 = 1_000_000_000;

   let n = sc.next::<usize>().ok().unwrap();

   let mut grid = Vec::new();

   for i in 1..=n {
      let mut row = Vec::new();

      for _ in 0..i {
         row.push(sc.next::<i32>().ok().unwrap());
      }

      grid.push(row);
   }

   let mut dp = grid.clone();

   for i in 1..n {
      for j in 0..=i {
         let value = dp[i][j];
         let mut best = value;

         if j < i {
            best = best.max(dp[i - 1][j] + value);
         }

         if j > 0 {
            best = best.max(value + dp[i - 1][j - 1]);
         }

         dp[i][j] = best;
      }
   }

   let result = dp.last().as_ref().unwrap().iter().max().unwrap();

   writeln!(handle, "{}", result).ok();
}
