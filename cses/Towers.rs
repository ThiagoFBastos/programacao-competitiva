#![allow(unused_imports)]
use std::cmp::Ordering;
use std::collections::{VecDeque, HashMap};
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

   let mut dp = vec![i32::MAX; n];

   let mut towers = 0;

   for _ in 0..n {
      let size = sc.next::<i32>().ok().unwrap();

      let pos = dp.binary_search_by(|candidate| match candidate.cmp(&size) {
         Ordering::Equal => Ordering::Less,
         ord => ord
      }).unwrap_err();

      if dp[pos] == i32::MAX {
         towers += 1;
      }

      dp[pos] = size;
   }

   writeln!(handle, "{towers}").ok();
 }