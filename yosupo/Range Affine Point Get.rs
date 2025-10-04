#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};

use crate::data_structures::{Function, SegTree};

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

mod data_structures {

   #[derive(Copy, Clone)]
   pub struct Function<const MOD: i64> {
      a: i64,
      b: i64
   }

   impl<const MOD: i64> Function<MOD> {
      pub fn new(a: i64, b: i64) -> Self {

         Self {
            a: a,
            b: b
         }
      }

      pub fn combine(&self, other: Function<MOD>) -> Self {
         Function::new((self.a * other.a) % MOD, (self.a * other.b + self.b) % MOD)
      }

      pub fn evaluate(&self, x: i64) -> i64 {
         (self.a * x + self.b) % MOD
      }
   }

   pub struct SegTree {
      data: Vec<Function<998244353>>,
      lazy: Vec<Function<998244353>>,
      marked: Vec<bool>,
      length: usize
   }

   impl SegTree {

      pub fn new(n: usize) -> Self {

         Self {
            data: vec![Function::new(1, 0); 4 * n],
            lazy: vec![Function::new(1, 0); 4 * n],
            marked: vec![false; 4 * n],
            length: n
         }
      }

      fn push(&mut self, p: usize) {
         if !self.marked[p] {
            return;
         }

         for i in 0..2 {
            let q = 2 * p + i;

            self.lazy[q] = self.lazy[p].combine(self.lazy[q]);
            self.data[q] = self.lazy[p].combine(self.data[q]);
            self.marked[q] = true;
         }

         self.marked[p] = false;
         self.lazy[p] = Function::new(1, 0);
      }

      fn update(&mut self, f: Function<998244353>, l: usize, r: usize, lo: usize, hi: usize, p: usize) {
         if r < lo || l > hi {
            return;
         } else if lo >= l && hi <= r {
            self.marked[p] = true;
            self.data[p] = f.combine(self.data[p]);
            self.lazy[p] = f.combine(self.lazy[p]);
            return;
         }

         let mid = (lo + hi) / 2;

         self.push(p);

         self.update(f, l, r, lo, mid, 2 * p);
         self.update(f, l, r, mid + 1, hi, 2 * p + 1);
      }

      fn query(&mut self, k: usize, lo: usize, hi: usize, p: usize) -> Function<998244353> {
         if lo == hi {
            return self.data[p];
         }

         let mid = (lo + hi) / 2;

         self.push(p);

         if k <= mid {
            return self.query(k, lo, mid, 2 * p);
         }

         return self.query(k, mid + 1, hi, 2 * p + 1);
      }

      pub fn apply(&mut self, l: usize, r: usize, f: Function<998244353>) {
         self.update(f, l, r, 0, self.length - 1, 1);
      }

      pub fn get(&mut self, k: usize) -> Function<998244353> {
         self.query(k, 0, self.length - 1, 1)
      }
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let q = sc.next::<usize>().ok().unwrap();

   let values = (0..n).map(|_| sc.next::<i64>().ok().unwrap()).collect::<Vec<_>>();

   let mut st = SegTree::new(n);

   for _  in 0..q {

      let t = sc.next::<u8>().ok().unwrap();

      if t == 0 {
         let l = sc.next::<usize>().ok().unwrap();
         let r = sc.next::<usize>().ok().unwrap();
         let a = sc.next::<i64>().ok().unwrap();
         let b = sc.next::<i64>().ok().unwrap();

         st.apply(l, r - 1, Function::new(a, b));
      } else {
         let pos = sc.next::<usize>().ok().unwrap();
         
         let f = st.get(pos);

         writeln!(handle, "{}", f.evaluate(values[pos])).ok();
      }
   }
 }
