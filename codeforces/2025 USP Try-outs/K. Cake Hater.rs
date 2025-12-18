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

   let n = sc.next::<usize>().unwrap();
   let a = sc.next::<usize>().unwrap();
   let b = sc.next::<usize>().unwrap();

   let mut bad = vec![false; a + 1];

   for _ in 0..b {
      let ingredient = sc.next::<usize>().unwrap();
      bad[ingredient] = true;
   }

   for i in 1..=n {
      let m = sc.next::<usize>().unwrap();
      let mut count = 0;

      for _ in 0..m {
         let ingredient = sc.next::<usize>().unwrap();

         if bad[ingredient] {
            count += 1;
         }
      }

      if 3 * count > m {
         writeln!(handle, "{}", i).ok();
         return;
      }
   }

   writeln!(handle, "-1").ok();
}
