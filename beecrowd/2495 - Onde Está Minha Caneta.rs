#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::*;
use std::collections::*;

struct Scanner {
   buffer : VecDeque<String>,
   eof: bool
}
 
impl Scanner {
 
   fn new() -> Scanner {
      Scanner {
         buffer: VecDeque::new(),
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

      if input.ends_with('\n') {
         input.pop();
         if input.ends_with('\r') {
            input.pop();
         }
      }

      return input;
   }

   fn is_eof(&self) -> bool {
      self.eof
   }
}

fn main() {

   let mut sc = Scanner::new();

   loop {

      let n = sc.next::<usize>();

      if sc.is_eof() {
         break;
      }

      let mut pencils: usize = 0;

      for i in 1..=n {
         pencils ^= i;
      }

      for _i in 1..n {
         let p = sc.next::<usize>();
         
         pencils ^= p;
      }

      println!("{}", pencils);
   }
}