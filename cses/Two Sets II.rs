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

fn bin_exp(mut n: i64, mut p: i64, modulo: i64) -> i64 {
   let mut result = 1;

   while p > 0 {
      if p & 1 == 1 {
         result = result * n % modulo;
      }

      n = n * n % modulo;
      p >>= 1;
   }

   result
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const MAXN: usize = 125250;
   const MOD: i64 = 1_000_000_007;

   let n = sc.next::<usize>().ok().unwrap();

   let m = n * (n + 1) / 2 + 1;

   if (m - 1) % 2 == 1 {
      writeln!(handle, "0").ok();
      return;
   }

   let mut dp = vec![0; MAXN + 1];

   dp[0] = 1;

   for i in 1..=n {
      for j in (i..m-1).rev() {
         dp[j] = (dp[j] + dp[j - i]) % MOD;
      }
   }

   let result = dp[(m - 1) / 2] * bin_exp(2, MOD - 2, MOD) % MOD;

   writeln!(handle, "{}", result).ok();
}
