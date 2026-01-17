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

impl Constants for i32 {
   fn initial() -> Self {
       return 0;
   }
}

struct MO {
   array: Vec<usize>,
   fenwick: FenwickTree<i32, fn(i32, i32) -> i32>,
   answer: i64,
   elements: i32
}

impl MO {

   fn new(array: &Vec<usize>) -> Self {

      Self {
         array: array.clone(),
         fenwick: FenwickTree::new(array.len(), |a: i32, b: i32| { return a + b; }),
         answer: 0,
         elements: 0
      }
   }

   fn add(&mut self, value: usize, left: bool) {
      if left {
         self.answer += self.fenwick.query(value as i32) as i64;
      } else {
         self.answer += self.elements as i64 - self.fenwick.query(value as i32 + 1) as i64;
      }

      self.elements += 1;
      self.fenwick.update(value as i32 + 1, 1);
   }

   fn rem(&mut self, value: usize, left: bool) {

      self.elements -= 1;
      self.fenwick.update(value as i32 + 1, -1);

      if left {
         self.answer -= self.fenwick.query(value as i32) as i64;
      } else {
         self.answer -= self.elements as i64 - self.fenwick.query(value as i32 + 1) as i64;
      }
   }

   fn answer(&mut self, queries: &Vec<(usize, usize)>) -> Vec<i64> {
      let mut lo = 0;
      let mut hi = -1;
      let q = queries.len();

      const CHUNCK_SIZE: usize = 300;

      let mut queries = (0..q).map(|i| (queries[i].0, queries[i].1, i)).collect::<Vec<_>>();
      let mut answer = vec![0; q];

      queries.sort_by_key(|tuple| (tuple.0 / CHUNCK_SIZE, tuple.1));

      for (l, r, i) in queries {

         while hi < r as i32 {
            hi += 1;
            self.add(self.array[hi as usize], false);
         }

         while hi > r as i32 {
            self.rem(self.array[hi as usize], false);
            hi -= 1;
         }

         while lo < l as i32 {
            self.rem(self.array[lo as usize], true);
            lo += 1;
         }

         while lo > l as i32 {
            lo -= 1;
            self.add(self.array[lo as usize], true);
         }

         answer[i] = self.answer;
      }

      return answer;
   }
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let mut values = (0..n).map(|_| sc.next::<usize>().unwrap()).collect::<Vec<_>>();

   let mut sorted_values = values.clone();

   sorted_values.sort();
   sorted_values.dedup();

   for value in values.iter_mut() {
      *value = sorted_values.binary_search(value).unwrap();
   }

   let mut queries = Vec::with_capacity(q);

   for _ in 0..q {
      let l = sc.next::<usize>().unwrap();
      let r = sc.next::<usize>().unwrap();

      queries.push((l, r - 1));
   }

   let mut mo = MO::new(&values);

   let answers = mo.answer(&queries);

   for value in answers {
      writeln!(writer, "{}", value).ok();
   }
}
