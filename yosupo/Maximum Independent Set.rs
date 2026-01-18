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
   let m = sc.next::<usize>().unwrap();

   let mut adj = vec![0; n];

   for _ in 0..m {
      let u = sc.next::<usize>().unwrap();
      let v = sc.next::<usize>().unwrap();

      adj[u] |= 1 << v;
      adj[v] |= 1 << u;
   }

   let is_independent_set = |s, l, r| {

      for j in l..=r {
         if (s >> j) & 1 == 1 {
            let intersection = adj[j] & s;

            if intersection != 0 {
               return false;
            }
         }
      }

      return true;
   };

   let max_ind_set = if n <= 20 {
      let mut max_ind_set = (0, 0);

      for i in 0..(1usize << n) {
         if is_independent_set(i, 0, n - 1) {
            max_ind_set = max_ind_set.max((i.count_ones(), i));
         }
      }

      max_ind_set
   } else {

      let mid = n / 2;

      let mut max_ind_set = vec![(0, 0); 1 << mid];

      for i in 0..(1usize << mid) {

         if is_independent_set(i, 0, mid - 1) {
            max_ind_set[i] = (i.count_ones(), i);
         }

         for j in 0..mid {
            if (i >> j) & 1 == 1 {
               max_ind_set[i] = max_ind_set[i].max(max_ind_set[i ^ (1 << j)]);
            }
         }
      }

      let mut max_global_ind_set = (0, 0);

      for i in 0..(1usize << (n - mid)) {

         if is_independent_set(i << mid, mid, n - 1) {
            let mut neighbours = 0;

            for j in 0..(n - mid) {
               if (i >> j) & 1 == 1 {
                  neighbours |= adj[j + mid];
               }
            }

            let complement = !neighbours & ((1 << mid) - 1);

            let (size, set) = max_ind_set[complement];

            max_global_ind_set = max_global_ind_set.max((size + i.count_ones(), set | (i << mid)));
         }
      }

      max_global_ind_set
   };

   let (x, s) = max_ind_set;

   writeln!(writer, "{}", x).ok();

   for u in 0..n {
      if (s >> u) & 1 == 1 {
         write!(writer, "{} ", u).ok();
      }
   }

   write!(writer, "\n").ok();   
}
