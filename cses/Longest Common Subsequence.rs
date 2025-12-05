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

   const INF: i32 = 1_000_000_000;

   let n = sc.next::<usize>().ok().unwrap();
   let m = sc.next::<usize>().ok().unwrap();

   let a = (0..n).map(|_| sc.next::<i32>().ok().unwrap()).collect::<Vec<_>>();
   let b = (0..m).map(|_| sc.next::<i32>().ok().unwrap()).collect::<Vec<_>>();

   let mut dp = vec![vec![INF; m + 2]; n + 2];

   dp[n][m] = 0;

   for i in (0..n).rev() {
      for j in (0..m).rev() {

         if i < n && j < m && a[i] == b[j] {
            dp[i][j] = dp[i + 1][j + 1] + 1;
         }

         dp[i][j] = dp[i][j].max(dp[i + 1][j].max(dp[i][j + 1]));
      }
   }

   let mut target = dp[0][0];
   let mut i = 0;
   let mut j = 0;

   let mut sequence = Vec::new();

   while i < n && j < m {
      if a[i] == b[j] && dp[i][j] == target {
         sequence.push(a[i]);
         i += 1;
         j += 1;
         target -= 1;
      } else if dp[i + 1][j] == target {
         i += 1;
      } else if dp[i][j + 1] == target {
         j += 1;
      } else {
         panic!("wrong solution");
      }
   }

   writeln!(handle, "{}", sequence.len()).ok();

   for value in sequence.iter() {
      write!(handle, "{} ", value).ok();
   }

   write!(handle, "\n").ok();
}
