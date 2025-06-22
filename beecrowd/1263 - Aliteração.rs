#![allow(unused_imports)]
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
 
   #[allow(dead_code)]
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

   #[allow(dead_code)]
   fn read_line(&mut self) -> String {
      let mut input = String::new();
         
      match std::io::stdin().read_line(&mut input) {
         Ok(0) => self.eof = true,
         Ok(_) => {},
         Err(e) => panic!("{}", e)
      };

      return input;
   }

   #[allow(dead_code)]
   fn is_eof(&self) -> bool {
      self.eof
   }
}

fn main() {
  
   let mut sc = Scanner::new();

   loop {
      let sentence = sc.read_line().to_lowercase();

      if sc.is_eof() {
         break;
      }

      let words: Vec<Vec<char>> = sentence.trim()
                                    .split_whitespace()
                                    .map(|x: &str| x.chars().collect())
                                    .collect();

      let mut answer = i32::default();
      let mut lo = usize::default();

      for i in 0..words.len() {

         if words[lo][0] != words[i][0] {
            if i - lo >= 2 {
               answer += 1;
            }

            lo = i;
         }
      }

      if words.len() - lo >= 2 {
         answer += 1;
      }

      println!("{}", answer);
   }
}