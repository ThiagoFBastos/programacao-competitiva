#![allow(unused_imports)]
use std::collections::{VecDeque, HashMap};
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

   let mut position = HashMap::new();

   let songs = (0..n).map(|_| sc.next::<i32>().ok().unwrap()).collect::<Vec<_>>();

   let mut current_pos = 0;
   let mut max_pos = 0;
   let mut j = 0;

   for i in 1..=n {
      let pos = *position.get(&songs[i - 1]).unwrap_or(&0);

      if pos >= j {
         j = pos + 1;
         current_pos = i - j + 1;
      } else {
         current_pos += 1;
      }

      max_pos = max_pos.max(current_pos);
      position.insert(songs[i - 1], i);
   }

   writeln!(handle, "{max_pos}").ok();
 }