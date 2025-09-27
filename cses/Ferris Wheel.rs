#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::cmp::Ordering;

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
   let w = sc.next::<i32>().ok().unwrap();

   let mut weight = (0..n).map(|_| sc.next::<i32>().ok().unwrap()).collect::<Vec<_>>();

   weight.sort();

   let mut count = 0;
   let mut lo = 0;
   let mut hi = n as i32 - 1;

   while lo <= hi {

      if weight[lo as usize] + weight[hi as usize] > w {
         hi -= 1;
      } else {
         lo += 1;
         hi -= 1;
      }

      count += 1;
   }

   writeln!(handle, "{count}").ok();
 }