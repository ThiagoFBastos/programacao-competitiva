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

   fn ignore(&mut self) {
      if !self.buffer.is_empty() {
         self.buffer.pop_front();
      }
   }
}

struct LazySegTree {
   min: Vec<i64>,
   lazy: Vec<i64>,
   n: usize
}

impl LazySegTree {

   fn build(&mut self, arr: &[i64], lo: usize, hi: usize, p: usize) {
      if lo == hi {
         self.min[p] = arr[lo];
         return;
      }

      let mid = (lo + hi) / 2;

      self.build(arr, lo, mid, 2 * p);
      self.build(arr, mid + 1, hi, 2 * p + 1);

      self.min[p] = self.min[2 * p].min(self.min[2 * p + 1]);
   }

   fn new(arr: &[i64]) -> Self {
      let n = arr.len();

      let mut st = Self {
         min: vec![0; 4 * n],
         lazy: vec![0; 4 * n],
         n: n
      };

      st.build(arr, 0, n - 1, 1);

      return st;
   }

   fn push(&mut self, p: usize) {
      if self.lazy[p] == 0 {
         return;
      }

      for i in 0..2 {
         let q = 2 * p + i;

         self.min[q] += self.lazy[p];
         self.lazy[q] += self.lazy[p];
      }

      self.lazy[p] = 0;
   }

   fn query(&mut self, lo: usize, hi: usize, l: usize, r: usize, p: usize) -> i64 {
      if hi < l || lo > r || l > r{
         return i64::MAX;
      } else if lo >= l && hi <= r {
         return self.min[p];
      }

      let mid = (lo + hi) / 2;

      self.push(p);

      let res1 = self.query(lo, mid, l, r, 2 * p);
      let res2 = self.query(mid + 1, hi, l, r, 2 * p + 1);

      return res1.min(res2);
   }

   fn update(&mut self, lo: usize, hi: usize, l: usize, r: usize, x: i64, p: usize) {
      if hi < l || lo > r || l > r{
         return;
      } else if lo >= l && hi <= r {
         self.min[p] += x;
         self.lazy[p] += x;
         return;
      }

      let mid = (lo + hi) / 2;

      self.push(p);

      self.update(lo, mid, l, r, x, 2 * p);
      self.update(mid + 1, hi, l, r, x, 2 * p + 1);

      self.min[p] = self.min[2 * p].min(self.min[2 * p + 1]);
   }
}

fn main() {
   let mut handle = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let arr = (0..n).map(|_| sc.next::<i64>().unwrap()).collect::<Vec<_>>();

   let mut st = LazySegTree::new(&arr);

   for _ in 0..q {

      let t = sc.next::<u8>().unwrap();
      let l = sc.next::<usize>().unwrap();
      let r = sc.next::<usize>().unwrap() - 1;

      if t == 0 {
         let x = sc.next::<i64>().unwrap();

         st.update(0, n - 1, l, r, x, 1);
      } else {
         let result = st.query(0, n - 1, l, r, 1);

         writeln!(handle, "{}", result).ok();
      }
   }
}
