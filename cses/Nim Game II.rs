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

   (0..tests).for_each(|_| {

      let n = sc.next::<usize>().ok().unwrap();

      match (0..n).map(|_| sc.next::<i32>().ok().unwrap() & 3)
                  .reduce(|a, b| a ^ b)
      {
         Some(xor) => {
            if xor != 0 {
               writeln!(handle, "first").ok();
            } else {
               writeln!(handle, "second").ok();
            }
         },
         None => {
            panic!("empty input");
         }
      }
   });
}