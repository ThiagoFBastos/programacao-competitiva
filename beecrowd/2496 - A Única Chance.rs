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

   let cases = sc.next::<usize>();

   for _i in 0..cases {

      let n = sc.next::<usize>();

      let str = sc.next::<String>();

      let chars = str.chars().collect::<Vec<char>>();

      let mut wrong_places = 0;

      for j in 0..n {

         let target = ('A' as u8 + j as u8) as char;
         let chr = chars[j];

         if chr != target {
            wrong_places += 1;
         }
      }

      if wrong_places == 2 {
         println!("There are the chance.");
      } else {
         println!("There aren't the chance.");
      }
   }
}