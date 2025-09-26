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

fn next_permutation(str: &mut Vec<char>) -> bool {
   let n = str.len();

   for i in (0..n).rev() {
      let mut max = (char::MAX, n);

      for j in i+1..n {
         if str[j] > str[i] {
            max = max.min((str[j], j));
         }
      }

      if max.1 < n {
         let j = max.1;

         (str[i], str[j]) = (str[j], str[i]);
         str[i+1..n].sort();
         
         return true;
      }
   }

   return false;
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let mut str = sc.next::<String>().ok().unwrap().chars().collect::<Vec<char>>();

   let mut words = Vec::new();

   str.sort();

   loop {

      words.push(str.iter().collect::<String>());

      if !next_permutation(&mut str) {
         break;
      }
   }

   writeln!(handle, "{}", words.len()).ok();

   for word in words.iter() {
      writeln!(handle, "{}", word).ok();
   }
}