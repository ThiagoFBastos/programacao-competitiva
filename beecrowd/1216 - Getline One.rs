#![allow(unused_imports)]
use std::cmp::*;
use std::collections::*;

struct Scanner {
   buffer : std::collections::VecDeque<String>,
   eof: bool
}
 
impl Scanner {
 
   fn new() -> Scanner {
      Scanner {
         buffer: std::collections::VecDeque::new(),
         eof: false
      }
   }
 
   fn next<T : std::str::FromStr + Default >(&mut self) -> T {
 
      if self.buffer.len() == 0 {
         let mut input = String::new();
         
         match std::io::stdin().read_line(&mut input) {
            Ok(0) => self.eof = true,
            Ok(_) => {},
            Err(e) => panic!("panico {}", e)
         };

         for word in input.split_whitespace() {
            self.buffer.push_back(word.to_string())
         }
      }

      if self.eof {
         return T::default();
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      front.parse::<T>().ok().unwrap()
   }

   fn read_line(&mut self) -> String {
      let mut input = String::new();
         
      match std::io::stdin().read_line(&mut input) {
         Ok(0) => self.eof = true,
         Ok(_) => {},
         Err(e) => panic!("panico {}", e)
      };

      return input;
   }

   fn is_eof(&mut self) -> bool {
      return self.eof;
   }
}

fn main() {
  
   let mut scanner = Scanner::new();

   let mut sum = i32::default();
   let mut cnt = i32::default();

   loop {

      let _name = scanner.read_line();

      if scanner.is_eof() {
         break;
      }

      let dist = scanner.next::<i32>();

      sum += dist;
      cnt += 1;
   }

   if cnt == 0 {
      println!("0.0");
      return;
   }

   let avg = (sum as f64) / (cnt as f64);

   println!("{:.1}", avg);
}