#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::ops::{Add, AddAssign, Sub};

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
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

struct Fenwick<T> {
   sum: Vec<T>,
   length: usize
}

impl<T: Copy + Default + AddAssign> Fenwick<T> {

   fn new(n: usize) -> Self {

      Self {
         sum: vec![T::default(); n + 1],
         length: n
      }
   }

   fn update(&mut self, mut k: usize, value: T) {

      if k == 0 || k > self.length {
         panic!("index out of bounds");
      }

      while k <= self.length {
         self.sum[k] += value;
         k += ((k as i32) & -(k as i32)) as usize;
      }
   }

   fn query(&self, mut k: usize) -> T {
      let mut answer = T::default();

      while k > 0 {
         answer += self.sum[k];
          k -= ((k as i32) & -(k as i32)) as usize;
      }

      answer
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let q = sc.next::<usize>().ok().unwrap();

   let values = (0..n).map(|_| sc.next::<i64>().ok().unwrap()).collect::<Vec<_>>();

   let mut ft = Fenwick::new(n);

   for i in 0..n {
      ft.update(i + 1, values[i]);
   }

   for _  in 0..q {
      let method = sc.next::<u8>().ok().unwrap();

      if method == 0 {
         let pos = sc.next::<usize>().ok().unwrap();
         let incremment = sc.next::<i64>().ok().unwrap();

         ft.update(pos + 1, incremment);
      } else {
         let l = sc.next::<usize>().ok().unwrap();
         let r = sc.next::<usize>().ok().unwrap();

         writeln!(handle, "{}", ft.query(r) - ft.query(l)).ok();
      }
   }
 }
