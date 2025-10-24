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
         self.buffer.push_back(String::from(""));
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn factorize(n: i32) -> Vec<i32> {
   let mut factors = Vec::new();
   let mut i = 1;

   while i * i <= n {
      if n % i == 0 {
         factors.push(i);

         if n != i * i {
            factors.push(n / i);
         }
      }

      i += 1;
   }

   factors
}

fn bin_exp(mut n: i64, mut p: i64, modulo: i64) -> i64 {
   let mut answer = 1;

   while p > 0 {
      if p & 1 == 1 {
         answer = answer * n % modulo;
      }

      n = n * n % modulo;
      p >>= 1;
   }

   answer
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const MOD: i64 = 1_000_000_007;

   let n = sc.next::<i32>().ok().unwrap();
   let m = sc.next::<i64>().ok().unwrap();

   let mut factors = factorize(n);

   factors.sort();

   let mut dp = vec![0; factors.len()];

   for (i, val) in dp.iter_mut().enumerate() {
      *val = bin_exp(m, factors[i]as i64, MOD);
   }

   for i in 0..factors.len() {
      for j in i + 1..factors.len() {
         if factors[j] % factors[i] != 0 {
            continue;
         }

         dp[j] -= dp[i];

         if dp[j] < 0 {
            dp[j] += MOD;
         }
      }
   }

   let mut answer = 0;

   for i in 0..factors.len() {
      answer = (answer + dp[i] * bin_exp(factors[i] as i64, MOD - 2, MOD)) % MOD;
   }

   writeln!(handle, "{}", answer).ok();
 }
