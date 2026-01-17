/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-17
 */

#![allow(unused_imports)]
#![allow(dead_code)]
use core::time;
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

trait Constants {

   fn initial() -> Self; // the initial constant
}

#[derive(Clone)]
struct FenwickTree<T, OP> {
   sum: Vec<T>, // the fenwick tree data
   length: usize, // the number of elements of the fenwick tree
   op: OP // the binary operator to apply an operation in the fenwick tree
}

impl<T: Constants + Copy, OP: Fn(T, T) -> T> FenwickTree<T, OP> {

    /**
     * create a new instance of FenwickTree
     * @param length the number of elements of the Fenwick Tree
     * @param op the binary function that handles with operations
     * @return the new instance of FenwickTree
     */
   fn new(length: usize, op: OP) -> Self {

      Self {
         sum: vec![T::initial(); length + 1],
         length,
         op
      }
   }

   /**
    * find the result of an operation of first k elements
    * @param k the number of the first elements for which we want to find the result
    */
   fn query(&self, mut k: i32) -> T {
      let mut sum = T::initial();

      assert!(k <= self.length as i32);

      while k > 0 {
         sum = (self.op)(sum, self.sum[k as usize]);
         k -= k & -k;
      }

      sum
   }

   /**
    * update a value to the element at position k 
    * @param k the position for which we want to modify
    * @param value the value for which we want to apply
    */
   fn update(&mut self, mut k: i32, value: T) {

      assert!(k > 0);

      while k <= self.length as i32 {
         self.sum[k as usize] = (self.op)(self.sum[k as usize], value);
         k += k & -k;
      }
   }
}

impl Constants for (i32, i64) {

   fn initial() -> Self {
      (0, 0)
   }
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let mut sweep = Vec::with_capacity(n + q);
   let mut answer = vec![(0, 0); q];

   let operation = |a: (i32, i64), b: (i32, i64)| {
      return (a.0 + b.0, a.1 + b.1);
   };

   let mut ft = FenwickTree::new(n, operation);

   for i in 0..n {
      let value = sc.next::<i32>().unwrap();
      sweep.push((value, 0, i, 0, 0));
   }

   for i in 0..q {
      let l = sc.next::<usize>().unwrap();
      let r = sc.next::<usize>().unwrap();
      let x = sc.next::<i32>().unwrap();

      if l < r {
         sweep.push((x, 1, l, r - 1, i));
      }
   }

   sweep.sort();

   for (x, t, l, r, pos) in sweep {
      if t == 0 {
         ft.update(l as i32 + 1, (1, x as i64));
      } else {
         let (count_left, sum_left) = ft.query(l as i32);
         let (count_right, sum_right) = ft.query(r as i32 + 1);

         answer[pos].0 = count_right - count_left;
         answer[pos].1 = sum_right - sum_left;
      }
   }

   for (count, sum) in answer {
      writeln!(writer, "{} {}", count, sum).ok();
   }
}
