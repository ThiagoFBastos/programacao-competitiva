/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-17
 */

#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};
use std::ops::{AddAssign, Mul, Neg, Sub};

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

trait Conversions {
   fn from_usize(value: usize) -> Self;
}

trait Constants {
   fn zero() -> Self;
   fn one() -> Self;
}

#[derive(Clone)]
struct FenwickTreeRange<T> {
   sum: Vec<Vec<T>>,
   size: usize
}

impl<T: Copy + Constants + AddAssign + Conversions + Mul<Output = T> + Sub<Output = T> + Neg<Output = T>> FenwickTreeRange<T> {

   fn new(size: usize) -> Self {

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

   fn add(&mut self, l: usize, r: usize, value: T) {
      self.update(0, l as i32, (T::from_usize(l) - T::one()) * value);
      self.update(0, r as i32 + 1, T::from_usize(r) * -value);
      self.update(1, l as i32, value);
      self.update(1, r as i32 + 1, -value);
   }

   fn prefix(&self, k: usize) -> T {
      return T::from_usize(k) * self.query(1, k as i32) - self.query(0, k as i32);
   }

   fn sum(&self, l: usize, r: usize) -> T {
      return self.prefix(r) - self.prefix(l - 1);
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

#[derive(Clone)]
pub struct LCA {
   adj: Vec<Vec<(usize, i64)>>,
   depth: Vec<i32>,
   st: Vec<Vec<usize>>,
   low: Vec<usize>,
   high: Vec<usize>,
   time: usize,
   ft: FenwickTreeRange<i64>
}

impl LCA {

   pub fn new(n: usize) -> Self {

      assert_ne!(n, 0);

      let lg = 32 - (n as i32).leading_zeros();

      Self {
         adj: vec![vec![]; n],
         depth: vec![0; n],
         st: vec![vec![0; lg as usize]; n],
         low: vec![0; n],
         high: vec![0; n],
         time: 0,
         ft: FenwickTreeRange::new(n)
      }
   }

   fn dfs(&mut self, u: usize, p: usize) {
      self.st[u][0] = p;
      self.low[u] = self.time;
      self.time += 1;

      for i in 1..self.st[u].len() {
         self.st[u][i] = self.st[self.st[u][i - 1]][i - 1];
      }

      for (v, _ ) in self.adj[u].clone() {
         if v == p {
            continue;
         }

         self.depth[v] = 1 + self.depth[u];
         self.dfs(v, u);
      }

      self.high[u] = self.time - 1;
   }

   pub fn build(&mut self, root: usize) {
      self.depth[root] = 0;
      self.dfs(root, root);
   }

   pub fn add_edge(&mut self, u: usize, v: usize, w: i64) {
      self.adj[u].push((v, w));
      self.adj[v].push((u, w));
   }

   fn query(&self, mut u: usize, mut v: usize) -> usize {
      if self.depth[u] > self.depth[v] {
         std::mem::swap(&mut u, &mut v);
      }

      let height = self.depth[v] - self.depth[u];

      if height != 0 {
         let lg = 31 - height.leading_zeros() as usize;
         
         for i in 0..=lg {
            if (height >> i) & 1 == 1 {
               v = self.st[v][i];
            } 
         }
      }

      if u == v {
         return u;
      }

      let lg = 31 - self.depth[u].leading_zeros() as usize;

      for i in (0..=lg).rev() {
         if self.st[u][i] == self.st[v][i] {
            continue;
         }

         u = self.st[u][i];
         v = self.st[v][i];
      }

      return self.st[u][0];
   }

   fn add(&mut self, u: usize, value: i64) {
      self.ft.add(self.low[u] + 1, self.high[u] + 1, value);
   }

   fn get_sum(&self, u: usize, v: usize) -> i64 {
      let x = self.query(u, v);
      let y = self.st[x][0];

      let u_sum = self.ft.sum(self.low[u] + 1, self.low[u] + 1);
      let v_sum = self.ft.sum(self.low[v] + 1, self.low[v] + 1);
      let x_sum = self.ft.sum(self.low[x] + 1, self.low[x] + 1);
      let x_without_parent_sum = x_sum - self.ft.sum(self.low[y] + 1, self.low[y] + 1);

      return u_sum + v_sum - 2 * x_sum + x_without_parent_sum;
   }
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let values = (0..n).map(|_| sc.next::<i32>().unwrap()).collect::<Vec<_>>();

   let mut lca = LCA::new(n + 1);

   lca.add_edge(0, 1, 0);

   for _ in 1..n {
      let u = sc.next::<usize>().unwrap();
      let v = sc.next::<usize>().unwrap();

      lca.add_edge(u + 1, v + 1, 0);
   }

   lca.build(0);

   for i in 1..=n {
      lca.add(i, values[i - 1] as i64);
   }

   for _ in 0..q {
      let t = sc.next::<u8>().unwrap();

      if t == 0 {
         let u = sc.next::<usize>().unwrap() + 1;
         let x = sc.next::<i64>().unwrap();
         lca.add(u, x);
      } else {
         let u = sc.next::<usize>().unwrap() + 1;
         let v = sc.next::<usize>().unwrap() + 1;
         writeln!(writer, "{}", lca.get_sum(u, v)).ok();
      }
   }
}
