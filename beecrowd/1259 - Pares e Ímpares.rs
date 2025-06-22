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

   let mut numbers: Vec<i32> = vec![0; n];

   for i in 0..n {
      numbers[i] = scanner.next::<i32>();
   }

   numbers.sort_by_key(|x| if x % 2 == 0 { (0, *x) } else { (1, -x) });

   for num in numbers.into_iter() {
      println!("{}", num);
   }
}