/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-15
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

trait Constants {

   fn initial() -> Self;
}

#[derive(Clone)]
struct FenwickTree<T, OP> {
   sum: Vec<T>,
   length: usize,
   op: OP
}

impl<T: Constants + Copy, OP: Fn(T, T) -> T> FenwickTree<T, OP> {

    /**
     * create a new instance of FenwickTree
     * @param length the number of elements of Fenwick Tree
     * @param op the binary function that handles with operations
     * @return the new instance of FenwickTree with zero values 
     */
   fn new(length: usize, op: OP) -> Self {

      Self {
         sum: vec![T::initial(); length + 1],
         length,
         op
      }
   }

   /**
    * find the sum of first k elements
    * @param k the number of the first elements for which we want to calculate the sum
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
    * add a value to the element at position k 
    * @param k the position for which we want to modify
    * @param value the value for which we want to sum
    */
   fn update(&mut self, mut k: i32, value: T) {

      assert!(k > 0);

      while k <= self.length as i32 {
         self.sum[k as usize] = (self.op)(self.sum[k as usize], value);
         k += k & -k;
      }
   }
}

impl Constants for i64 {

   fn initial() -> Self {
       return 0;
   }
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let mut sweep = Vec::with_capacity(2 * n + q);
   let mut coords = Vec::with_capacity(n + 2 * q);

   for _ in 0..n {
      let x = sc.next::<i32>().unwrap();
      let y = sc.next::<i32>().unwrap();
      let w = sc.next::<i32>().unwrap();

      coords.push(y);
      sweep.push((x, 1, y, w, 0));
   }

   for i in 0..q {
      let l = sc.next::<i32>().unwrap();
      let d = sc.next::<i32>().unwrap();
      let r = sc.next::<i32>().unwrap();
      let u = sc.next::<i32>().unwrap();

      coords.push(d);
      coords.push(u);

      sweep.push((l, 0, d, u, i));
      sweep.push((r - 1, 2, d, u, i));
   }

   coords.sort();
   coords.dedup();
   sweep.sort();

   let operation = |a: i64, b: i64| {
      return a + b;
   };

   let mut ft = FenwickTree::new(coords.len(), operation);
   let mut answer = vec![0; q];

   let position = |x| {
      return coords.binary_search(&x).unwrap();
   };

   for (_, t, a, b, c) in sweep {

      if t == 0 {
         let bottom = position(a);
         let top = position(b);
         answer[c] -= ft.query(top as i32) - ft.query(bottom as i32);
      } else if t == 1 {
         let pos = position(a);
         ft.update(pos as i32 + 1, b as i64);
      } else if t == 2 {
         let bottom = position(a);
         let top = position(b);
         answer[c] += ft.query(top as i32) - ft.query(bottom as i32);
      }
   }

   for value in answer {
      writeln!(writer, "{}", value).ok();
   }
}
