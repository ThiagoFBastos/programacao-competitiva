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

   let mut height = (0..2*n).map(|k| {
      let mut value = sc.next::<i32>().ok().unwrap();

      if k % 2 == 1 {
         value *= -1;
      }

      value
   }).collect::<Vec<_>>();

   height.sort_by_key(|val| val.abs());

   let mut person = 0;
   let mut max_person = 0;

   for h in height.iter() {

      if *h > 0 {
         person += 1;
         max_person = max_person.max(person);
      } else {
         person -= 1;
      }
   }

   writeln!(handle, "{max_person}").ok();
 }