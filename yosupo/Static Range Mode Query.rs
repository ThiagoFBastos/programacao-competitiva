/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-17
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
   let q = sc.next::<usize>().unwrap();

   let mut values = (0..n).map(|_| sc.next::<usize>().unwrap()).collect::<Vec<_>>();

   let mut values_sorted = values.clone();

   values_sorted.sort();
   values_sorted.dedup();

   for value in values.iter_mut() {
      *value = values_sorted.binary_search(value).unwrap();
   }

   let m = values_sorted.len();

   let mut frequency = vec![0; m];
   let mut table = vec![vec![]; n + 1];
   let mut mode = (0, 0);

   let mut update = |value: usize, add: bool, mode: &mut (usize, usize)| {
      if add {
         frequency[value] += 1;
         table[frequency[value]].push(value);

         if mode.0 + 1 == frequency[value] {
            mode.0 += 1;
            mode.1 = value;
         }

      } else {

         frequency[value] -= 1;

         while mode.0 > 0 {
            let mut exists = false;

            while !table[mode.0].is_empty() {
               let last = *table[mode.0].last().unwrap();

               if frequency[last] < mode.0 {
                  table[mode.0].pop();
               } else {
                  exists = true;
                  break;
               }
            }

            if exists {
               break;
            }

            mode.0 -= 1;
         }
      }

      if !table[mode.0].is_empty() {
         mode.1 = *table[mode.0].last().unwrap();
      }
   };

   let mut queries = Vec::with_capacity(q);
   let mut answer = vec![(0, 0); q];

   for i in 0..q {
      let l = sc.next::<usize>().unwrap();
      let r = sc.next::<usize>().unwrap() - 1;

      queries.push((l, r, i));
   }

   const CHUNK_SIZE: usize = 256;

   queries.sort_by_key(|tuple| (tuple.0 / CHUNK_SIZE, tuple.1));

   let mut lo = 0;
   let mut hi = -1;

   for (l, r, index) in queries {

      while hi < r as i32 {
         hi += 1;
         update(values[hi as usize], true, &mut mode);
      }

      while hi > r as i32 {
         update(values[hi as usize], false, &mut mode);
         hi -= 1;
      }

      while lo < l as i32 {
         update(values[lo as usize], false, &mut mode);
         lo += 1;
      }

      while lo > l as i32 {
         lo -= 1;
         update(values[lo as usize], true, &mut mode);
      }

      answer[index] = (values_sorted[mode.1], mode.0);
   }

   for (value, count) in answer {
      writeln!(writer, "{} {}", value, count).ok();
   }
}
