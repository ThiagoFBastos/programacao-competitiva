#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::Write;

struct Scanner {
   buffer: VecDeque<String>
}
 
impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new()
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> T {
 
      if self.buffer.is_empty() {
         let mut input = String::new();
         
         std::io::stdin().read_line(&mut input).ok();
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      front.parse::<T>().ok().unwrap()
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let tests = sc.next::<usize>();

   (0..tests).for_each(|_| {

      let n = sc.next::<usize>();

      let xor = (0..n).map(|_| sc.next::<i32>())
                      .reduce(|a, b| a ^ b)
                      .unwrap();

      if xor != 0 {
         writeln!(handle, "first").ok();
      } else {
         writeln!(handle, "second").ok();
      }
   });
}