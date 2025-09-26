#![allow(unused_imports)]
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

   let tests = sc.next::<usize>().ok().unwrap();

   for _ in 0..tests {
      let n = sc.next::<usize>().ok().unwrap();
      let a = sc.next::<usize>().ok().unwrap();
      let b = sc.next::<usize>().ok().unwrap();

      if a + b > n || (a == 0 && b > 0) || (a > 0 && b == 0) {
         writeln!(handle, "NO").ok();
         continue;
      }

      writeln!(handle, "YES").ok();

      let mut games = Vec::new();

      let wins = a + b;

      for i in wins + 1..=n {
         games.push((i, i));
      }

      for i in 1..=wins {
         games.push((i, (a + i - 1) % wins + 1));
      }

      for (c1, _) in games.iter() {
         write!(handle, "{} ", c1).ok();
      }

      write!(handle, "\n").ok();

      for (_, c2) in games.iter() {
         write!(handle, "{} ", c2).ok();
      }

      write!(handle, "\n").ok();
   }
 }