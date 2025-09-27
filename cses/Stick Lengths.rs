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

   let n = sc.next::<usize>().ok().unwrap();

   let mut length = (0..n).map(|_| sc.next::<i64>().ok().unwrap()).collect::<Vec<_>>();

   length.sort();

   let mut prefix = vec![0; n + 1];

   for i in 1..=n {
      prefix[i] = prefix[i - 1] + length[i - 1];
   }

   let mut min_operations = i64::MAX;

   for i in 1..=n {      
      min_operations = min_operations.min(length[i - 1] * (2 * i as i64 - n as i64) + prefix.last().unwrap() - 2 * prefix[i]);
   }

   writeln!(handle, "{}", min_operations).ok();
 }