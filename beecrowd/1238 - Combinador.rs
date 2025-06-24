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

      return input;
   }

   fn is_eof(&self) -> bool {
      self.eof
   }
}

fn combine(str1: &String, str2: &String) -> String {
   let mut result = String::new();
   let mut i: usize = 0;
   let mut j: usize = 0;

   let a = str1.chars().collect::<Vec<char>>();
   let b = str2.chars().collect::<Vec<char>>();

   while i < a.len() && j < b.len() {
      if (i + j) % 2 == 0 {
         result.push(a[i]);
         i += 1;
      } else {
         result.push(b[j]);
         j += 1;
      }
   }

   while i < a.len() {
      result.push(a[i]);
      i += 1;
   }

   while j < b.len() {
      result.push(b[j]);
      j += 1;
   }

   return result;
}

fn main() {

   let mut sc = Scanner::new();

   let tests = sc.next::<usize>();

   for _i in 0..tests {
      let str1 = sc.next::<String>();
      let str2 = sc.next::<String>();

      let result = combine(&str1, &str2);

      println!("{}", result);
   }
}