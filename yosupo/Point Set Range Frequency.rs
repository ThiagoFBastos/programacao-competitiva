/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-18
 */

#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};
use std::ops::AddAssign;

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

#[derive(Clone)]
struct FenwickTree<T> {
   sum: Vec<T>,
   length: usize
}

impl<T: Default + Copy + AddAssign> FenwickTree<T> {

    /**
     * create a new instance of FenwickTree
     * @param length the number of elements of Fenwick Tree
     * @return the new instance of FenwickTree with zero values 
     */
   fn new(length: usize) -> Self {

      Self {
         sum: vec![T::default(); length + 1],
         length
      }
   }

   /**
    * find the sum of first k elements
    * @param k the number of the first elements for which we want to calculate the sum
    */
   fn query(&self, mut k: i32) -> T {
      let mut sum = T::default();

      assert!(k <= self.length as i32);

      while k > 0 {
         sum += self.sum[k as usize];
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
         self.sum[k as usize] += value;
         k += k & -k;
      }
   }
}

struct OrderedSet<T> {
   keys: Vec<T>,
   fenwick: FenwickTree<i32>,
   size: usize
}

impl<T: Ord + Eq + Copy + Clone> OrderedSet<T> {

   fn new(keys: &Vec<T>) -> Self {

      let n = keys.len();
      let mut stored_keys = keys.clone();

      stored_keys.sort();
      stored_keys.dedup();

      Self {
         keys: stored_keys,
         fenwick: FenwickTree::new(n),
         size: n
      }
   }

   fn index_of_key(&self, key: T) -> usize {
      match self.keys.binary_search(&key) {
         Ok(index) | Err(index) => {
            return index;
         }
       }
   }

   fn insert(&mut self, key: T) {
      let index = self.index_of_key(key);

      assert!(index < self.size && self.keys[index] == key);

      self.fenwick.update(index as i32 + 1, 1);
   }

   fn remove(&mut self, key: T) {
      let index = self.index_of_key(key);

      assert!(index < self.size && self.keys[index] == key);

      self.fenwick.update(index as i32 + 1, -1);
   }

   fn order_of_key(&mut self, key: T) -> usize {
      let index = self.index_of_key(key);

      let count = self.fenwick.query(index as i32);

      assert!(count >= 0);

      return count as usize;
   }
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();
   
   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   // corner case
   if n == 0 {
      _ = sc.next::<String>().unwrap();

      for _ in 0..q {
         let t = sc.next::<u8>().unwrap();

         if t == 0 {
            _ = sc.next::<usize>().unwrap();
            _ = sc.next::<i32>().unwrap();
         } else {
            _ = sc.next::<usize>().unwrap();
            _ = sc.next::<usize>().unwrap();
            _ = sc.next::<i32>().unwrap();
            writeln!(writer, "0").ok();
         }
      }      
      return;
   }

   let mut values = (0..n).map(|_| sc.next::<i32>().unwrap()).collect::<Vec<_>>();

   let mut queries = Vec::with_capacity(q);
   let mut keys = Vec::with_capacity(n + q);

   for (index, &value) in values.iter().enumerate() {
      keys.push((value, index));
   }

   for _ in 0..q {
      let t = sc.next::<u8>().unwrap();

      if t == 0 {
         let k = sc.next::<usize>().unwrap();
         let v = sc.next::<i32>().unwrap();

         keys.push((v, k));
         queries.push((t, k, 0, v));
      } else {
         let l = sc.next::<usize>().unwrap();
         let r = sc.next::<usize>().unwrap();
         let x = sc.next::<i32>().unwrap();

         queries.push((t, l, r, x));
      }
   }

   let mut os = OrderedSet::new(&keys);

   for (index, &value) in values.iter().enumerate() {
      os.insert((value, index));
   }

   for i in 0..q {
      if queries[i].0 == 0 {
         let (_, k, _, v) = queries[i];

         os.remove((values[k], k));
         os.insert((v, k));
         values[k] = v;
      } else {
         let (_, l, r, x) = queries[i];

         let count = os.order_of_key((x, r)) - os.order_of_key((x, l));

         writeln!(writer, "{}", count).ok();
      }
   } 
}
