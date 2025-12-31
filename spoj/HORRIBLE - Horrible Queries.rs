#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};

use crate::data_structures::ranges::*;

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
}

mod data_structures {

   pub mod ranges {
    use std::ops::{AddAssign, Mul, Neg, Sub};

      pub trait Conversions {
         fn from_usize(value: usize) -> Self;
      }

      pub trait Constants {
         fn zero() -> Self;
         fn one() -> Self;
      }

      #[derive(Clone)]
      pub struct FenwickTreeRange<T> {
         sum: Vec<Vec<T>>,
         size: usize
      }

      impl<T: Copy + Constants + AddAssign + Conversions + Mul<Output = T> + Sub<Output = T> + Neg<Output = T>> FenwickTreeRange<T> {

         pub fn new(size: usize) -> Self {

            Self {
               sum: vec![vec![T::zero(); size + 1]; 2],
               size
            }
         }

         fn update(&mut self, bit_pos: usize, mut k: i32, value: T) {

            assert!(k >= 1);

            while k <= self.size as i32 {
               self.sum[bit_pos][k as usize] += value;
               k += k & -k;
            }
         }

         fn query(&self, bit_pos: usize, mut k: i32) -> T {
            assert!(k <= self.size as i32);

            let mut result = T::zero();

            while k > 0 {
               result += self.sum[bit_pos][k as usize];
               k -= k & -k;
            }

            result
         }

         pub fn add(&mut self, l: usize, r: usize, value: T) {
            self.update(0, l as i32, (T::from_usize(l) - T::one()) * value);
            self.update(0, r as i32 + 1, T::from_usize(r) * -value);
            self.update(1, l as i32, value);
            self.update(1, r as i32 + 1, -value);
         }

         fn prefix(&self, k: usize) -> T {
            return T::from_usize(k) * self.query(1, k as i32) - self.query(0, k as i32);
         }

         pub fn sum(&self, l: usize, r: usize) -> T {
            return self.prefix(r) - self.prefix(l - 1);
         }
      }
   }
}

impl Constants for i64 {
   fn zero() -> Self {
       return 0;
   }

   fn one() -> Self {
       return 1;
   }
}

impl Conversions for i64 {
   fn from_usize(value: usize) -> Self {
       return value as i64;
   }
}

fn main() {
   let mut handle = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let t = sc.next::<usize>().unwrap();

   for _ in 0..t {

      let n = sc.next::<usize>().unwrap();
      let q = sc.next::<usize>().unwrap();

      let mut ft = FenwickTreeRange::new(n);

      for _ in 0..q {
         let t = sc.next::<u8>().unwrap();
         let l = sc.next::<usize>().unwrap();
         let r = sc.next::<usize>().unwrap();

         if t == 0 {
            let x = sc.next::<i64>().unwrap();
            ft.add(l, r, x);
         } else {
            writeln!(handle, "{}", ft.sum(l, r)).ok();
         }
      }
   }  
}
