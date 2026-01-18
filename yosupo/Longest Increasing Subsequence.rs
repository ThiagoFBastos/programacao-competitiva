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

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();
   
   let n = sc.next::<usize>().unwrap();

   let values = (0..n).map(|_| sc.next::<i32>().unwrap()).collect::<Vec<_>>();

   let mut lis = vec![(i32::MAX, 0); n];
   let mut link = vec![(0, None); n];
   let mut answer = 0;

   for (k, &value) in values.iter().enumerate() {
      let index = lis.binary_search_by(|element| match element.0.cmp(&value) {
         std::cmp::Ordering::Equal => std::cmp::Ordering::Greater,
         ord => ord
      }).unwrap_err();

      lis[index] = (value, k);
      link[k] = (index + 1, if index > 0 { Some(lis[index - 1].1) } else { None });
      answer = answer.max(index + 1);
   }

   writeln!(writer, "{}", answer).ok();

   let node = link.iter().enumerate().find(|element| element.1.0 == answer).unwrap();
   let mut list = Vec::new();
   let mut index = node.0;

   loop {
      list.push(index);

      if link[index].1.is_none() {
         break;
      }

      index = link[index].1.unwrap();
   }

   list.reverse();

   for index in list {
      write!(writer, "{} ", index).ok();
   }

   write!(writer, "\n").ok();
}
