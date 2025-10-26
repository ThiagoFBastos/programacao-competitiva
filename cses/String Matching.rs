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

   let s = sc.next::<String>().ok().unwrap();
   let t = sc.next::<String>().ok().unwrap();
   let pattern = format!("{}.{}", t, s);

   let chars = pattern.chars().collect::<Vec<_>>();

   let mut kmp = Vec::with_capacity(pattern.len());

   kmp.push(0);

   for i in 1..chars.len() {
      let mut k = kmp[i - 1];

      while k > 0 && chars[k as usize] != chars[i] {
         k = kmp[k as usize - 1];
      }

      if chars[k as usize] == chars[i] {
         k += 1;
      }

      kmp.push(k);
   }
   
   let mut count = 0;

   for i in t.len() + 1..chars.len() {
      if kmp[i] == t.len() as i32 {
         count += 1;
      }
   }

   writeln!(handle, "{count}").ok();
 }
