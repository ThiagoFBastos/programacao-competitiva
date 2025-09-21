#![allow(unused_imports)]
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
               return Err(Error::new(ErrorKind::UnexpectedEof, "End Of Line"));
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

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
   
   const MOD: i64 = 1_000_000_007;

   let n = sc.next::<usize>().ok().unwrap();

   let mut dp = vec![0; n + 1];
   let mut pow = vec![0; n + 1];
   let mut frequency = vec![0; n + 1];

   for _ in 0..n {
      let value = sc.next::<usize>().ok().unwrap();
      frequency[value] += 1;
   }

   pow[0] = 1;
   for i in 1..=n {
      pow[i] = pow[i - 1] << 1;
      if pow[i] >= MOD {
         pow[i] -= MOD;
      }
   }

   for i in 1..=n {
      for j in (i..=n).step_by(i) {
         dp[i] += frequency[j] as i64;
      }
      dp[i] = (pow[dp[i] as usize] - 1 + MOD) % MOD;
   }

   for i in (1..=n).rev() {
      for j in (2*i..=n).step_by(i) {
         dp[i] -= dp[j];
         if dp[i] < 0 {
            dp[i] += MOD;
         }
      }
   }

   for i in 1..=n {
      write!(handle, "{} ", dp[i]).ok();
   }

   write!(handle, "\n").ok();
}