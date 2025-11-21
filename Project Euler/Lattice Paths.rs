#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, HashMap};
use std::io::{self, Error, ErrorKind, Write};
use std::ops::Add;

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

   let n = sc.next::<usize>().ok().unwrap() + 1;

   // eu faria usando combinatória, mas não conseguiria sem usar um inteiro maior que u128

   let mut dp = vec![vec![0_u64; n + 1]; n + 1];

   dp[0][0] = 1;

   for i in 0..n {
      for j in 0..n {
         dp[i + 1][j] += dp[i][j];
         dp[i][j + 1] += dp[i][j];
      }
   }

   writeln!(handle, "{}", dp[n - 1][n - 1]).ok();
}
