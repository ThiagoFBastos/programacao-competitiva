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
 
   let mut sc = Scanner::new();

   const MAX_ADJACENT_DIGITS: usize = 13;

   let digits = sc.next::<String>().ok().unwrap()
                        .chars()
                        .map(|c| c.to_digit(10).unwrap())
                        .collect::<Vec<_>>();

   let n = digits.len();
   let mut max_product = 0;

   for i in 0..n - MAX_ADJACENT_DIGITS + 1 {

      let mut product = 1;

      for j in 0..MAX_ADJACENT_DIGITS {
         product *= digits[i + j] as i64;
      }

      max_product = max_product.max(product);
   }

   writeln!(handle, "{}", max_product).ok();
}
