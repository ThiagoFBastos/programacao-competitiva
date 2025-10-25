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

fn bin_exp(n: i64, p: i64, modulo: i64) -> i64 {
   if p == 0 {
      return 1;
   }

   let value = bin_exp(n, p >> 1, modulo);

   let mut result = value * value % modulo;

   if p & 1 == 1 {
      result = result * n % modulo;
   }

   return result;
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<i64>().ok().unwrap();

   if n == 1 {
      writeln!(handle, "2").ok();
      return;
   }

   const MOD: i64 = 1_000_000_007;

   let x = bin_exp(2, n * n, MOD);
   let y = bin_exp(2, n * n / 4, MOD) * (n % 2 + 1);
   let z = (bin_exp(2,n * n / 2, MOD) * (n % 2 + 1) - y + MOD) % MOD;
   let answer = ((x - y - z) * bin_exp(4, MOD - 2, MOD) + z * bin_exp(2, MOD - 2, MOD) + y) % MOD;

   writeln!(handle, "{}", (answer + MOD) % MOD).ok();
 }
