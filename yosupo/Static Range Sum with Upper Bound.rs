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

   let mut sweep = Vec::with_capacity(n + q);
   let mut answer = vec![(0, 0); q];
   let mut ft_sum = FenwickTree::new(n);
   let mut ft_count = FenwickTree::new(n);

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
         ft_count.update(l as i32 + 1, 1);
         ft_sum.update(l as i32 + 1, x as i64);
      } else {
         answer[pos].0 = ft_count.query(r as i32 + 1) - ft_count.query(l as i32); 
         answer[pos].1 = ft_sum.query(r as i32 + 1) - ft_sum.query(l as i32);
      }
   }

   for (count, sum) in answer {
      writeln!(writer, "{} {}", count, sum).ok();
   }
}
