#![allow(unused_imports)]
use std::collections::{VecDeque, BTreeMap};
use std::io::{self, Error, ErrorKind, Write};
use std::ops::Bound::*;

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
   let m = sc.next::<usize>().ok().unwrap();

   let mut prices = BTreeMap::new();

   for _ in 0..n {
      let h = sc.next::<i32>().ok().unwrap();

      let count = *prices.get(&h).unwrap_or(&0);

      prices.insert(h, count + 1);
   }

   for _ in 0..m {
      let t = sc.next::<i32>().ok().unwrap();

      if prices.is_empty() {
         writeln!(handle, "-1").ok();
      } else {

         let mut range = prices.range((Unbounded, Included(t)));

         if let Some((first, second)) = range.next_back() {
            let key = *first;

            writeln!(handle, "{}", key).ok();

            let count = *second;

            prices.insert(key,count - 1);

            if count == 1 {
               prices.remove(&key);
            }
         } else {
            writeln!(handle, "-1").ok();
         }
      }
   }
 }