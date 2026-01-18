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

fn manacher(s: &String) -> (Vec<usize>, Vec<usize>) {
   let n = s.len();
   let str = s.chars().collect::<Vec<_>>();

   let mut d1 = vec![1; n];
   let mut d2 = vec![0; n];

   let mut l = 0;
   let mut r = -1;
   let mut len = 0;
   
   for i in 0..n {

      if i as i32 <= r {
         d1[i] = d1[l + r as usize - i].min(r as usize + 1 - i);
         d2[i] = d2[l + r as usize + 1 - i].min(r as usize + 1 - i);
      }

      while i + d1[i] < n && i >= d1[i] && str[i - d1[i]] == str[i + d1[i]] {
         d1[i] += 1;
      }

      while i + d2[i] < n && i >= d2[i] + 1 && str[i - d2[i] - 1] == str[i + d2[i]] {
         d2[i] += 1;
      }

      if r < i as i32 + d2[i] as i32 - 1 {
         l = i - d2[i];
         r = i as i32 + d2[i] as i32 - 1;
      }

      if r < i as i32 + d1[i] as i32 - 1 {
         l = i + 1 - d1[i];
         r = i as i32 + d1[i] as i32 - 1;
      }

      if r == n as i32 - 1 {
         len = len.max(r as usize + 1 - l);
      }
   }

   (d1, d2)
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();
   
   let s = sc.next::<String>().unwrap();

   let (d1, mut d2) = manacher(&s);

   d2.drain(0..1);

   let n = d1.len() + d2.len();

   for i in 0..n {
      if i % 2 == 0 {
         write!(writer, "{} ", 2 * d1[i / 2] - 1).ok();
      } else {
         write!(writer, "{} ", 2 * d2[i / 2]).ok();
      }
   }

   write!(writer, "\n").ok();
}
