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

fn max_digit_count(mut n: u64) -> u64 {
   let mut f = [0; 10];
   let mut p = 1;
   let mut m = 1;
   let mut k = 0;

   while n > 0 {
      let digit = n % 10;

      f[digit as usize] += m;

      for d in 0..digit {
         f[d as usize] += p;
      }

      for d in 0..9 {
         f[d] += digit * (p / 10) * k;
      }

      m += p * digit;
      n /= 10;
      p *= 10;
      k += 1;
   }

   f[0] -= p / 10;

   return *f.iter().max().unwrap();
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);

   let mut sc  = Scanner::new();

   let n = sc.next::<u64>().unwrap();

   let mut low = 9;
   let mut high = 1_000_000_000_000_000_001;

   while low < high {
      let mid = (low + high) / 2;

      if max_digit_count(mid) > n {
         high = mid;
      } else {
         low = mid + 1;
      }
   }

   writeln!(handle, "{}", high - 1).ok();
}
