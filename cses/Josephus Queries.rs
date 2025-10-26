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

fn kth_josephus(mut n: i64, mut k: i64) -> i64 {
   let mut f = 1;
   let mut step = 1;
   let mut x = -1;

   while n > 0 {
      if k <= n / 2 {
         x = f + step * (1 + 2 * (k - 1));
         break;
      } else if n & 1 == 1 {
         k -= (n + 1) / 2;

         if k == 0 {
            x = f;
            break;
         }

         f += step << 1;
         n -= 1;
      } else {
         k -= n / 2;
      }

      n >>= 1;
      step <<= 1;
   }

   x
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let t = sc.next::<usize>().ok().unwrap();

   for _ in 0..t {
      let n = sc.next::<i64>().ok().unwrap();
      let k = sc.next::<i64>().ok().unwrap();

      writeln!(handle, "{}", kth_josephus(n, k)).ok();
   }
 }
