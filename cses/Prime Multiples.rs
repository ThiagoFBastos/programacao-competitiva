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
         self.buffer.push_back(String::from(""));
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<i64>().ok().unwrap();
   let k = sc.next::<usize>().ok().unwrap();

   let permutation = (0..k).map(|_| sc.next::<i64>().ok().unwrap()).collect::<Vec<_>>();

   let mut answer = 0;

   for i in 1..(1 << k) {
      let mut x = 1;
      let mut cnt = -1;

      for j in 0..k {

         if (i >> j) & 1 == 1 {
            cnt *= -1;
            if permutation[j] > n / x {
               x = -1;
               break;
            }
            x *= permutation[j];
         }
      }

      if x != -1 {
         answer += n / x * cnt;
      }
   }

   writeln!(handle, "{}", answer).ok();
 }
