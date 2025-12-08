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

   const N: usize = 18;
   const MOD: i64 = 1_000_000_007;

   let n = sc.next::<usize>().unwrap();

   let mut dp = vec![0; 1 << N];
   let mut pow = vec![0; 1 << N];

   for _ in 0..n {
      let x = sc.next::<usize>().unwrap();
      dp[x] += 1;
   }

   pow[0] = 1;
   for i in 1..=n {
      pow[i] = pow[i - 1] << 1;
      if pow[i] >= MOD {
         pow[i] -= MOD;
      }
   }

   for i in 0..N {
      for j in (0..=n).rev() {
         if (!j >> i) & 1 == 1 {
            dp[j] += dp[j ^ (1 << i)];
         }
      }
   }

   for i in 0..=n {
      dp[i] = (pow[dp[i] as usize] - 1) % MOD;

      if i.count_ones() % 2 == 1 {
         dp[i] = (MOD - dp[i]) % MOD;
      } 
   }

   for i in 0..N {
      for j in (0..=n).rev() {
         if (!j >> i) & 1 == 1 {
            dp[j] += dp[j ^ (1 << i)];

            if dp[j] >= MOD {
               dp[j] -= MOD;
            }
         }
      }
   }

   for i in 0..=n {
      let mut answer = dp[i];

      if i.count_ones() % 2 == 1 {
         answer = (MOD - answer) % MOD;
      }

      write!(handle, "{} ", answer).ok();
   }

   write!(handle, "\n").ok();
}
