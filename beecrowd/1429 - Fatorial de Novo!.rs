#![allow(unused_imports)]
use std::cmp::*;
use std::collections::*;

struct Scanner {
   buffer : std::collections::VecDeque<String>
}
 
impl Scanner {
 
   fn new() -> Scanner {
      Scanner {
         buffer: std::collections::VecDeque::new()
      }
   }
 
   fn next<T : std::str::FromStr >(&mut self) -> T {
 
      if self.buffer.len() == 0 {
         let mut input = String::new();
         std::io::stdin().read_line(&mut input).ok();
         for word in input.split_whitespace() {
            self.buffer.push_back(word.to_string())
         }
      }
 
      let front = self.buffer.pop_front().unwrap();
      front.parse::<T>().ok().unwrap()
   }
}

fn acm(x: i32) -> i32 {
   let fat = [1, 2, 6, 24, 120];

   let mut y = x;
   let mut i = usize::default();
   let mut ans = i32::default();

   while y > 0 {
      let d = y % 10;
      ans += d * fat[i];
      i += 1;
      y /= 10;
   }

   return ans;
}

fn main() {
   let mut scanner = Scanner::new();

   loop {

      let x = scanner.next::<i32>();

      if x == 0 {
         break;
      }

      println!("{}", acm(x));
   }
}