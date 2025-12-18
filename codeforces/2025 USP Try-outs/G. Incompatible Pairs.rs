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

   _ = sc.next::<usize>().unwrap();
   let str = sc.next::<String>().unwrap().chars().collect::<Vec<_>>();
   let mut stack = 0;
   let mut open_parentheses = 0;
   let mut open_current_parentheses = 0;
   let mut pairs = 0;

   for &c in str.iter() {

      if c == '(' {
         open_current_parentheses += 1;
         stack += 1;
      } else {
         stack -= 1;
         pairs += open_parentheses as i64;

         if stack == 0 {
            open_parentheses += open_current_parentheses;
            open_current_parentheses = 0;
         }
      }
   }

   writeln!(handle, "{}", pairs).ok();
 }
