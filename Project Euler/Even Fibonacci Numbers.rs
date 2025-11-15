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

   let max = sc.next::<i64>().ok().unwrap();

   let mut fib = vec![1_i64, 2_i64];

   let mut i = 2;

   while *fib.last().unwrap() < max {
      fib.push(fib[i - 1] + fib[i - 2]);
      i += 1;
   }

   fib.pop();

   let sum = fib.iter().filter(|n| *n % 2 == 0).sum::<i64>();

   writeln!(handle, "{}", sum).ok();
}
