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

fn to_lowercase(c: char) -> char {
   return c.to_lowercase().next().unwrap();
}

fn main() {
   let mut scanner = Scanner::new();

   let n = scanner.next::<usize>();

   for _i in 0..n {
      let mut line = String::new();
      let mut frq: Vec<i32> = vec![0; 128];

      std::io::stdin().read_line(&mut line).ok();

      let chars: Vec<char> = line.chars().collect();

      for c in chars.into_iter() {      
         if c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' {
            frq[to_lowercase(c) as usize] += 1;
         }
      }

      let begin = 'a' as usize;
      let end = 'z' as usize;

      let max = *frq.iter().max().unwrap();

      for i in begin..=end {
         if frq[i] == max {
            print!("{}", i as u8 as char);
         }
      }

      print!("\n");
   }
}