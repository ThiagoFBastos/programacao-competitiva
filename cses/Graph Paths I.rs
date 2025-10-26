#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::ops::{Add, Mul, Rem};

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
 
      if self.buffer.is_empty() {
         self.buffer.push_back("".to_string());
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

trait Constants {
   fn zero() -> Self;
   fn one() -> Self;
}

impl Constants for i64 {
   fn zero() -> Self {
      0
   }

   fn one() -> Self {
      1
   }
}

#[derive(Clone)]
struct Matrix<T> {
   container: Vec<Vec<T>>,
   rows: usize,
   columns: usize
}

impl<T: Copy + Add<Output = T> + Mul<Output = T> + Rem<Output = T> + Constants> Matrix<T> {

   fn new(rows: usize, columns: usize) -> Self {

      Self {
         container: vec![vec![T::zero(); columns]; rows],
         rows: rows,
         columns: columns
      }
   }

   fn identity(rows: usize, columns: usize) -> Self {
      let mut container = Matrix::<T>::new(rows, columns);

      for i in  0..rows {
         for j in 0..columns {
            container.set(i, j, if i == j { T::one() } else { T::zero() })
         }
      }

      container
   }

   fn multiply(&self, other: &Matrix<T>, modulo: T) -> Self {

      if self.columns != other.rows {
         panic!("rows != columns");
      }

      let mut result = Matrix::<T>::new(self.rows, other.columns);
      
      for i in 0..self.rows {
         for j in 0..other.columns {
            for k in 0..self.columns {
               result.container[i][j] = (result.container[i][j] + self.container[i][k] * other.container[k][j]) % modulo;
            }
         }
      }

      result
   }

   fn set(&mut self, x: usize, y: usize, value: T) {
      self.container[x][y] = value;
   }

   fn get(&self, x: usize, y: usize) -> T {
      self.container[x][y]
   }

   fn pow(&self, mut p: u64, modulo: T) -> Self {

      if self.rows != self.columns {
         panic!("rows != columns");
      }

      let mut answer = Matrix::<T>::identity(self.rows, self.columns);
      let mut matrix = self.clone();

      while p > 0 {

         if p & 1 == 1 {
            answer = answer.multiply(&matrix, modulo)
         }

         matrix = matrix.multiply(&matrix, modulo);

         p >>= 1;
      }

      answer
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const MOD: i64 = 1_000_000_007;

   let n = sc.next::<usize>().ok().unwrap();
   let m = sc.next::<usize>().ok().unwrap();
   let k = sc.next::<usize>().ok().unwrap();

   let mut adj = Matrix::<i64>::new(n, n);

   for _ in 0..m {
      let u = sc.next::<usize>().ok().unwrap() - 1;
      let v = sc.next::<usize>().ok().unwrap() - 1;

      adj.set(u, v, adj.get(u, v) + 1);
   }

   let answer = adj.pow(k as u64, MOD);

   writeln!(handle, "{}", answer.get(0, n - 1)).ok();
 }
