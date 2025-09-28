#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::mem::swap;

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
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn seq_length(mut a: i32, mut b: i32) -> i32 {
   let mut k = 0;

   while a > 0 || b > 0 {
      if a < b {
         swap(&mut a, &mut b);
      }

      a -= b + 1;
      k += 1;

      if a < 0 {
         return i32::MAX;
      }
   }

   k
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();

   let mut answer = (i32::MAX, i32::MAX, i32::MAX);

   for a in 0..=n {
      let (x, y) = (a as i32, (n - a) as i32);
      answer = answer.min((seq_length(x, y), x, y));
   }

   let (_, mut _0, mut _1) = answer;

   let mut str = Vec::new();

   while _0 > 0 || _1 > 0 {
      if _0 < _1 {
         _1 -= _0 + 1;
         str.push('1');
      } else {
         _0 -= _1 + 1;
         str.push('0');
      }
   }

   let out = str.iter().collect::<String>();

   writeln!(handle, "{out}").ok();
 }