#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::ops::{Add, Sub};

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

struct PrefixSum<T> {
   sum: Vec<T>
}

impl<T: Copy + Default + Add<Output = T> + Sub<Output = T>> PrefixSum<T> {

   fn new(data: &[T]) -> Self {

      let n = data.len();

      let mut sum = vec![T::default(); n + 1];

      for i in 1..=n {
         sum[i] = sum[i - 1] + data[i - 1];
      }

      Self {
         sum: sum
      }
   }

   fn query(&self, l: usize, r: usize) -> T {
      self.sum[r] - self.sum[l - 1]
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let q = sc.next::<usize>().ok().unwrap();

   let data = (0..n).map(|_| sc.next::<i64>().ok().unwrap()).collect::<Vec<_>>();

   let prefix_sum = PrefixSum::new(&data);

   for _  in 0..q {
      let l = sc.next::<usize>().ok().unwrap();
      let r = sc.next::<usize>().ok().unwrap();

      writeln!(handle, "{}", prefix_sum.query(l + 1, r)).ok();
   }
 }
