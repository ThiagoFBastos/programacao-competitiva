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

struct RootedTree {
   adj: Vec<Vec<usize>>,
   low: Vec<usize>,
   high: Vec<usize>,
   time: usize,
   ft: FenwickTree<i64>
}

impl RootedTree {

   fn new(n: usize) -> Self {

      Self {
         adj: vec![vec![]; n],
         low: vec![0; n],
         high: vec![0; n],
         time: 0,
         ft: FenwickTree::new(n)
      }
   }

   fn add_edge(&mut self, p: usize, u: usize) {
      self.adj[p].push(u);
   }

   fn dfs(&mut self, u: usize) {
      self.low[u] = self.time;
      self.time += 1;

      for v in self.adj[u].clone() {
         self.dfs(v);
      }

      self.high[u] = self.time - 1;
   }

   fn build(&mut self) {
      self.dfs(0);
   }

   fn update(&mut self, u: usize, x: i64) {
      self.ft.update(self.low[u] as i32 + 1, x);
   }

   fn query(&self, u: usize) -> i64 {
      return self.ft.query(self.high[u] as i32 + 1) - self.ft.query(self.low[u] as i32);
   }
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let values = (0..n).map(|_| sc.next::<i32>().unwrap()).collect::<Vec<_>>();

   let mut tree = RootedTree::new(n);

   for i in 1..n {
      let p = sc.next::<usize>().unwrap();

      tree.add_edge(p, i);
   }

   tree.build();

   for (i, x) in values.into_iter().enumerate() {
      tree.update(i, x as i64);
   }

   for _ in 0..q {
      let t = sc.next::<u8>().unwrap();
      let u = sc.next::<usize>().unwrap();

      if t == 0 {
         let x = sc.next::<i64>().unwrap();
         tree.update(u, x);
      } else {
         let sum = tree.query(u);
         writeln!(writer, "{}", sum).ok();
      }
   }
}
