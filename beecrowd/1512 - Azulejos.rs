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

fn gcd(a: i64, b: i64) -> i64 {
   if b == 0 {
      return a;
   }

   return gcd(b, a % b);
}

fn lcm(a: i64, b: i64) -> i64 {
   return a * b / gcd(a, b);
}

fn main() {
  
  let mut scanner = Scanner::new();

  loop {
      let n = scanner.next::<i64>();
      let a = scanner.next::<i64>();
      let b = scanner.next::<i64>();

      if n == 0 && a == 0 && b == 0 {
         break;
      }
      
      let count = n / a + n / b - n / lcm(a, b);

      println!("{}", count);
  }
}