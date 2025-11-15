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

fn largest_prime_factor(mut n: i64) -> i64 {
   let mut i = 3;
   let mut max_factor= 0;

   if n % 2 == 0 {
      max_factor = 2;

      while n % 2 == 0 {
         n >>= 1;
      }
   }

   while i * i <= n {
      if n % i == 0 {

         while n % i == 0 {
            n /= i;
         }

         max_factor = max_factor.max(i);
      }

      i += 2;
   }

   if n > 1 {
      max_factor = max_factor.max(n);
   }

   max_factor
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   const N: i64 = 600_851_475_143;

   writeln!(handle, "{}", largest_prime_factor(N)).ok();
}
