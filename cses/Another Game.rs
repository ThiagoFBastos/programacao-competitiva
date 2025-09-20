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

   for _ in 0..tests {

      let n = sc.next::<i32>();

      let even = (0..n).map(|_| sc.next::<i32>())
                       .map(|x| !x & 1)
                       .sum::<i32>();

      if even == n {
         writeln!(handle, "second").ok();
      } else {
         writeln!(handle, "first").ok();
      }
   }  
}