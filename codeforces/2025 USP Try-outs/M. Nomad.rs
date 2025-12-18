#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, HashMap};
use std::{i32, vec};
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

   let n = sc.next::<usize>().unwrap();
   let days = sc.next::<i32>().unwrap();

   let mut d = (1..=n).map(|i| (sc.next::<i32>().unwrap(), i)).collect::<Vec<_>>();

   d.sort();
   d.reverse();

   if d[0].0 >= days {
      for _  in 0..days {
         write!(handle, "{} ", d[0].1).ok();
      }

      write!(handle, "\n").ok();
      return;
   } else if n == 1 || d[1].0 == 0 {
      writeln!(handle, "-1").ok();
      return;
   }

   let mut current = 0;
   let mut count_days = 0;

   for _  in 0..days {
      write!(handle, "{} ", d[current].1).ok();
      count_days += 1;
      if count_days == d[current].0 {
         count_days = 0;
         current ^= 1;
      }
   }

   write!(handle, "\n").ok();
}
