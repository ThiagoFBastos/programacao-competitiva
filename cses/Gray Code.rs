#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::str::FromStr;

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
               return Err(Error::new(ErrorKind::UnexpectedEof, "End Of Line"));
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

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let mut x = 0;

   let to_bin = |mut x, k| {
      let mut str = Vec::new();

      while x > 0 {
         str.push(if x % 2 == 1 { '1' } else { '0' });
         x /= 2;
      }

      while str.len() < k {
         str.push('0');
      }

      str.reverse();

      return str.iter().collect::<String>();
   };

   let mut values = (0..17).map(|_| Vec::new()).collect::<Vec<Vec<i32>>>();

   values[0] = vec![0];

   for k in 1..=n {
      for i in values[k - 1].clone().iter() {
         values[k].push(*i);
      }

      values[k - 1][0] = 1 << (k - 1);

      for i in values[k - 1].clone().iter() {
         values[k].push(*i);
      }
   }

   for y in values[n].iter() {
      x ^= *y;
      writeln!(handle, "{}", to_bin(x, n)).ok();
   }
}