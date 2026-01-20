/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-20
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

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let q = sc.next::<usize>().unwrap();

   let mut deque = VecDeque::new();

   for _ in 0..q {
      let t = sc.next::<u8>().unwrap();

      match t {
         0 => {
            let x = sc.next::<i32>().unwrap();
            deque.push_front(x);
         },
         1 => {
            let x = sc.next::<i32>().unwrap();
            deque.push_back(x);
         },
         2 => {
            deque.pop_front();
         },
         3 => {
            deque.pop_back();
         },
         4 => {
            let index = sc.next::<usize>().unwrap();
            writeln!(writer, "{}", deque[index]).ok();
         },
         _ => {
            panic!("wrong query type");
         }
      }
   }
}
