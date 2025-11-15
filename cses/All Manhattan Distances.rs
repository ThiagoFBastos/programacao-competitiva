#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};

struct Scanner {
   buffer: VecDeque<String>
}

impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new()
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
 
      if self.buffer.is_empty() {
         let mut input = String::new();
         
         match std::io::stdin().read_line(&mut input) {
            Ok(0) => {
               return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
            } Ok(_) => {
               
            } Err(e) => {
               return Err(e);
            }
         }
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();
      }
 
      if self.buffer.is_empty() {
         self.buffer.push_back("".to_string());
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();

   let mut x = Vec::with_capacity(n);
   let mut y = Vec::with_capacity(n);

   for _ in 0..n {
      let cx = sc.next::<i128>().ok().unwrap();
      let cy = sc.next::<i128>().ok().unwrap();

      x.push(cx);
      y.push(cy);
   }

   let sum_dist = |coords: &mut [i128]| {
      let mut ans = 0;
      let mut sum = 0;

      coords.sort();

      for i in 0..coords.len() {
         ans += i as i128 * coords[i] - sum;
         sum += coords[i];
      }

      ans
   };

   let distance = sum_dist(&mut x) + sum_dist(&mut y);

   writeln!(handle, "{}", distance).ok();
}
