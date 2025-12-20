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

   let n = sc.next::<usize>().unwrap();

   let mut sum = 0;
   let mut count = 0;
   let mut frequency = vec![0; n];

   frequency[0] = 1;

   for _ in 0..n {
      let value = sc.next::<i64>().unwrap();

      sum += value;

      let modulo = (sum % n as i64 + n as i64) % n as i64;

      count += frequency[modulo as usize] as i64;
      frequency[modulo as usize] += 1;
   }

   writeln!(handle, "{}", count).ok();
}
