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
         Err(e) => panic!("{}", e)
      };

      return input;
   }

   fn is_eof(&self) -> bool {
      self.eof
   }
}

fn main() {
  
   let mut sc = Scanner::new();

   loop {

      let trail = sc.next::<String>();

      if sc.is_eof() {
         break;
      }

      let processes = sc.next::<usize>();

      let operation: Vec<char> = trail.chars().collect();

      let mut cycles = i32::default();
      let mut lo = usize::default();

      for (i, op) in operation.clone().into_iter().enumerate() {

         if op == 'W' {
            if lo < i {
               cycles += 1;
            }
            cycles += 1;
            lo = i + 1;
         } else if i - lo + 1 == processes {
            cycles += 1;
            lo = i + 1;
         }
      }

      if lo < operation.len() {
         cycles += 1;
      }

      println!("{}", cycles);
   }
}