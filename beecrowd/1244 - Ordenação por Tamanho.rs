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

fn main() {
   let mut scanner = Scanner::new();

   let n: usize = scanner.next::<usize>();

   for _i in 0..n {
      let mut line = String::new();

      std::io::stdin().read_line(&mut line).ok();

      let mut words: Vec<&str> = line.trim()
                              .split_whitespace()
                              .collect();

      let m = words.len();

      words.sort_by_key(|s| -(s.len() as i32));

      for (i, word) in words.into_iter().enumerate() {
         print!("{}", word);
         if i < m - 1 {
            print!(" ");
         } else {
            print!("\n");
         }
      }
   }
}