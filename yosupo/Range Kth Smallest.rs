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

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let mut values = (0..n).map(|i| (sc.next::<i32>().unwrap(), i)).collect::<Vec<_>>();

   values.sort();

   let mut queries = Vec::with_capacity(q);
   let mut low = vec![0; q];
   let mut high = vec![n - 1; q];

   for _ in 0..q {
      let l = sc.next::<usize>().unwrap();
      let r = sc.next::<usize>().unwrap();
      let k = sc.next::<usize>().unwrap();

      queries.push((l, r - 1, k + 1));
   }

   let lg = 32 - (n as i32).leading_zeros() as usize;

   let mut table = vec![vec![]; n];

   for _ in 0..=lg {
      let mut ft = FenwickTree::new(n);

      for i in 0..n {
         table[i].clear();
      }

      for i in 0..q {
         if low[i] == high[i] {
            continue;
         }

         let mid = (low[i] + high[i]) / 2;

         table[mid].push(i); 
      }

      for i in 0..n {
         let (_ , pos) = values[i];

         ft.update(pos as i32 + 1, 1);

         for &index in table[i].iter() {
            let (l, r, k) = queries[index];

            let count = ft.query(r as i32 + 1) - ft.query(l as i32);

            if count >= k {
               high[index] = i;
            } else {
               low[index] = i + 1;
            }
         }
      }
   }

   for i in 0..q {
      let (x, _) = values[high[i]];
      writeln!(writer, "{}", x).ok();
   }
}
