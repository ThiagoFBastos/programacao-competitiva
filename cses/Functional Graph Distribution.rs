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

   let mut f = (0..=n).map(|_| vec![0; n + 1]).collect::<Vec<Vec<i64>>>();
   let mut c = (0..=n).map(|_| vec![0; n + 1]).collect::<Vec<Vec<i64>>>();
   let mut dp = vec![0 as i64; n + 1];
   let mut pt = vec![0 as i64; n + 1];

   f[0][0] = 1;
   c[0][0] = 1;
   pt[0] = 1;

   for i in 1..=n {
      pt[i] = n as i64 * pt[i - 1] % MOD;
   }

   for i in 1..=n {

      c[i][0] = 1;
      c[i][i] = 1;

      for j in 1..i {
         c[i][j] = c[i - 1][j] + c[i - 1][j - 1];

         if c[i][j] >= MOD {
            c[i][j] -= MOD;
         }
      }

      for j in 1..=n {
         f[i][j] = ((j - 1) as i64 * f[i][j - 1] + f[i - 1][j - 1]) % MOD;
      }
   }

   for i in (1..=n).rev() {
      for j in 1..=n {
         dp[i] = (dp[i] + f[i][j] * c[n][j] % MOD * pt[n - j]) % MOD;
      }
   }

   for i in (1..=n).rev() {
      dp[i] = (dp[i] + MOD) % MOD;
      for j in (1..i).rev() {
         dp[j] = (dp[j] - dp[i] * c[i][j]) % MOD;
      }
   }

   dp.remove(0);
   dp.iter().for_each(|value| { writeln!(handle, "{}", value).ok(); });
}