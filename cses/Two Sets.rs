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

   let n = sc.next::<usize>().ok().unwrap();

   let mut sum = n as i64 * (n as i64 + 1) / 2;

   if sum % 2 == 1 {
      writeln!(handle, "NO").ok();
   } else {
      let mut marked = vec![true; n + 1];
      let mut count = 0;

      writeln!(handle, "YES").ok();

      sum /= 2;

      for k in (1..=n).rev() {
         let i = k as i64;

         if sum >= i {
            sum -= i;
            marked[k] = false;
            count += 1;
         }
      }

      writeln!(handle, "{count}").ok();

      for k in 1..=n {
         if !marked[k] {
            write!(handle, "{k} ").ok();
         }
      }

      writeln!(handle, "\n{}", n - count).ok();

       for k in 1..=n {
         if marked[k] {
            write!(handle, "{k} ").ok();
         }
      }

      write!(handle, "\n").ok();
   }
}