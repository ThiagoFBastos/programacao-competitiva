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

fn bin_exp(n: i64, p: i64, modulo: i64) -> i64 {
   if p == 0 {
      return 1;
   }

   let mut result = bin_exp(n, p >> 1, modulo);

   result = result * result % modulo;

   return if p & 1 == 1 { result * n % modulo } else { result };
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const MOD: i64 = 1_000_000_007;

   let mut n = sc.next::<usize>().ok().unwrap();

   if n & 1 == 1 {
      writeln!(handle, "0").ok();
      return;
   }

   n >>= 1;

   let mut fat = vec![0; 2 * n + 1];

   fat[0] = 1;

   for i in 1..=2*n {
      fat[i] = i as i64 * fat[i - 1] % MOD;
   }

   let comb = move |n: usize, k: usize| {
      fat[n] * bin_exp(fat[k], MOD - 2, MOD) % MOD * bin_exp(fat[n - k], MOD - 2, MOD) % MOD
   };

   let answer = comb(2 * n, n) * bin_exp(n as i64 + 1, MOD - 2, MOD) % MOD;

   writeln!(handle, "{}", answer).ok();
 }
