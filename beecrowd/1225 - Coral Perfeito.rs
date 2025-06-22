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

   fn is_eof(&mut self) -> bool {
      return self.eof;
   }
}

fn main() {
  
   let mut sc = Scanner::new();

   loop {
      let n = sc.next::<usize>();

      if sc.is_eof() {
         break;
      }

      let mut arr: Vec<i32> = Vec::new();
      let mut sum = i32::default();

      for _i in 0..n {
         let val = sc.next::<i32>();

         arr.push(val);
         sum += val;
      }

      if sum % n as i32 != 0 {
         println!("-1");
         continue;
      }

      let target = sum / (n as i32);
      let mut answer = i64::default();

      for val in arr.into_iter() {
         answer += (val - target).abs() as i64;
      }

      println!("{}", answer / 2 + 1);
   }
}