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

   let tests = sc.next::<usize>().ok().unwrap();

   for _ in 0..tests {

      let x = sc.next::<i64>().ok().unwrap();
      let y = sc.next::<i64>().ok().unwrap();
      let n = x.max(y);

      let mut m = n * n;

      if n & 1 == 1 {
         let x0 = 1;
         let y0 = n;

         if y == y0 {
            m -= x - x0;
         } else {
            m -= n - 1 + y0 - y;
         }
      } else {
         let x0 = n;
         let y0 = 1;

         if x == x0 {
            m -= y - y0;
         } else {
            m -= n - 1 + x0 - x;
         }
      }

      writeln!(handle, "{m}").ok();
   }
}