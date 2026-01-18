/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-18
 */

#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};

struct Scanner {
   buffer: VecDeque<String>,
   reader: io::BufReader<io::Stdin>
}

impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new(),
         reader: io::BufReader::new(io::stdin())
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
 
      if self.buffer.is_empty() {
         let mut input = String::new();

         match self.reader.read_line(&mut input) {
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

         if self.buffer.is_empty() {
            self.buffer.push_back("".to_string());
         }
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }

   fn read_line(&mut self) -> io::Result<String> {
      let mut input = String::new();

      match self.reader.read_line(&mut input) {
         Ok(0) => {
            return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
         } Ok(_) => {
            
         } Err(e) => {
            return Err(e);
         }
      }

      Ok(input)
   }
}

fn z_function(s: &String) -> Vec<usize> {
   let n = s.len();
   let str = s.chars().collect::<Vec<_>>();
   let mut z = vec![0; n];

   let mut l = 0;
   let mut r = 0;

   for i in 1..n {
      if i <= r {
         z[i] = z[i - l].min(r - i + 1);
      }

      while i + z[i] < n && str[z[i]] == str[i + z[i]] {
         z[i] += 1;
      }

      if i + z[i] - 1 > r {
         l = i;
         r = i + z[i] - 1;
      }
   }

   return z;
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();
   
   let s = sc.next::<String>().unwrap();

   let mut z = z_function(&s);

   z[0] = s.len();

   for lcp in z {
      write!(writer, "{} ", lcp).ok();
   }

   write!(writer, "\n").ok();
}
