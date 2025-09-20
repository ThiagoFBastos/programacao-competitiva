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
   
   let n = sc.next::<i64>().ok().unwrap();

   let count = |k: i64| -> i64 {
      let mut answer = i64::default();
      let mut i = 1;

      while i <= n && k >= i {
         answer += n.min(k / i);
         i += 1;
      }

      answer
   };

   let mut lo = 1;
   let mut hi = n * n;
   let k = (hi + 1) / 2;

   while lo < hi {
      let mid = (lo + hi) / 2;

      if count(mid) >= k {
         hi = mid;
      } else {
         lo = mid + 1;
      }
   }

   writeln!(handle, "{hi}").ok();
}