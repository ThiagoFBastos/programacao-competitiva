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

fn from_binary(s: String) -> u32 {
   let chars = s.chars().collect::<Vec<char>>();
   let mut int = 0;

   for &c in chars.iter() {
      int <<= 1;
      int += c.to_digit(10).unwrap();
   }

   int
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
   
   let n = sc.next::<usize>().ok().unwrap();
   let _ = sc.next::<usize>().ok().unwrap();

   let bitmasks = (0..n).map(|_| sc.next::<String>().ok().unwrap())
                        .map(|s| from_binary(s))
                        .collect::<Vec<u32>>();

   let mut answer = u32::MAX;

   for i in 0..n {
      for j in i+1..n {
         answer = answer.min((bitmasks[i] ^ bitmasks[j]).count_ones());
      }
   }

   writeln!(handle, "{answer}").ok();
}