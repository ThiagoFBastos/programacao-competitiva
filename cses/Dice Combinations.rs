#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};

use crate::algebra::*;

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

mod algebra {
    use std::{marker::PhantomData, ops::{Add, Mul, Rem}, process::Output};

    #[derive(Clone)]
   pub struct Matrix<T> {
      container: Vec<Vec<T>>,
      rows: usize,
      columns: usize,
      modulo: T
   }

   pub trait Constants {
      fn zero() -> Self;
      fn one() -> Self;
   }

   impl<T: Default + Copy + Clone + Add<Output = T> + Mul<Output = T> + Rem<Output = T> + Ord + Constants> Matrix<T> {

      pub fn new(rows: usize, columns: usize, modulo: T) -> Self {

         Self {
            container: vec![vec![T::zero(); columns]; rows],
            rows: rows,
            columns: columns,
            modulo: modulo
         }
      }

      pub fn set(&mut self, x: usize, y: usize, value: T) {
         self.container[x][y] = value;
      }

      pub fn get(&self, x: usize, y: usize) -> T {
         self.container[x][y]
      }

      pub fn rows(&self) -> usize {
         self.rows
      }

      pub fn columns(&self) -> usize {
         self.columns
      }

      pub fn multiply(&self, other: &Matrix<T>) -> Matrix<T> {
         if self.columns != other.rows || self.modulo != other.modulo {
            panic!("invalid matrixes");
         }

         let mut result= Matrix::new(self.rows, other.columns, self.modulo);

         for i in 0..self.rows {
            for j in 0..other.columns {
               for k in 0..self.columns {
                  result.container[i][j] = (result.container[i][j] + self.container[i][k] * other.container[k][j]) % self.modulo;
               }
            }
         }

         result
      }

      pub fn pow(&self, mut n: u64) -> Matrix<T> {

         let mut result = Matrix::new(self.rows, self.columns, self.modulo);
         let mut matrix = self.clone();

         for x in 0..self.rows {
            for y in 0..self.columns {
               result.container[x][y] = if x == y { T::one() } else { T::zero() };
            }
         }

         while n > 0 {

            if n & 1 == 1 {
               result = result.multiply(&matrix);
            }

            matrix = matrix.multiply(&matrix);

            n >>= 1;
         }

         result
      }

   }
}

impl Constants for i64 {
   fn zero() -> Self {
      0
   }

   fn one() -> Self {
      1
   }
}
fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const MOD: i64 = 1_000_000_007;

   let n = sc.next::<i64>().ok().unwrap();

   let mut dp = [0; 7];

   dp[0] = 1;

   for i in 1..=6 {
      for j in 1..=6 {
         if i < j {
            break;
         }
         dp[i] += dp[i - j];
      }
   }

   if n <= 6 {
      writeln!(handle, "{}", dp[n as usize]).ok();
      return;
   }

   let mut rec = Matrix::new(6, 6, MOD);

   for i in 0..6 {
      rec.set(0, i, 1);
   }

   for i in 1..6 {
      rec.set(i, i - 1, 1);
   }

   let result = rec.pow(n as u64 - 6);

   let mut answer = 0;

   for i in 1..=6 {
      answer += dp[7 - i] * result.get(0, i - 1);
   }

   writeln!(handle, "{}", answer % MOD).ok();
 }