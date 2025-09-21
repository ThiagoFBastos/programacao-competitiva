#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};

use crate::data_structures::Fenwick;

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

mod data_structures {
    use std::{ops::{AddAssign, Sub}, process::Output};

   pub struct Fenwick<T> {
      sum: Vec<T>,
      n: usize
   }

   impl<T: Default + Copy + AddAssign + Sub<Output = T>> Fenwick<T> {

      pub fn new(n: usize) -> Self {
         Self {
            sum: vec![T::default(); n + 1],
            n: n
         }
      }

      pub fn query(&self, mut k: i32) -> T {
         let mut answer = T::default();

         while k > 0 {
            answer += self.sum[k as usize];
            k -= k & -k;
         }

         answer
      }

      pub fn update(&mut self, mut k: i32, value: T) {

         while k as usize <= self.n {
            self.sum[k as usize] += value;
            k += k & -k;
         }
      }

      pub fn query_range(&self, l: i32, r: i32) -> T {
         self.query(r) - self.query(l - 1)
      }
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
   
   let n = sc.next::<usize>().ok().unwrap();

   let mut ft = Fenwick::new(n);

   let mut arr = (1..=n).map(|i| {
      ft.update(i as i32, 1 as i64);
      (sc.next::<i32>().ok().unwrap(), i as i32)
   }).collect::<Vec<_>>();

   arr.sort();

   let mut count = 0;

   for i in 0..n {
      let (_, k) = arr[i];

      count += ft.query(k - 1).min(ft.query_range(k + 1, n as i32));

      ft.update(k, -1);
   }

   writeln!(handle, "{count}").ok();
}