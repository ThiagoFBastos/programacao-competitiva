#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};

use crate::ranges::SegTree;

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
               return Err(Error::new(ErrorKind::UnexpectedEof, "End Of Line"));
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

mod ranges {

   pub struct SegTree {
      st: Vec<i32>,
      lazy: Vec<i32>,
      n: usize
   }

   impl SegTree {

      pub fn new(n: usize) -> Self {
         Self {
            st: vec![0; 4 * n],
            lazy: vec![0; 4 * n],
            n: n
         }
      }

      fn push(&mut self, node: usize) {
         if self.lazy[node] == 0 {
            return;
         }

         for k in 0..2 {
            let child = 2 * node + k;
            self.st[child] += self.lazy[node];
            self.lazy[child] += self.lazy[node];
         }

         self.lazy[node] = 0;
      }

      fn apply(&mut self, x: i32, l: usize, r: usize, lo: usize, hi: usize, p: usize) {
         if l > r {
            return;
         } else if r - l == hi - lo {
            self.st[p] += x;
            self.lazy[p] += x;
            return;
         }

         let mid = (lo + hi) / 2;

         self.push(p);
         self.apply(x, l, r.min(mid), lo, mid, 2 * p);
         self.apply(x, l.max(mid + 1), r, mid + 1, hi, 2 * p + 1);

         self.st[p] = self.st[2 * p].min(self.st[2 * p + 1]);
      }

      fn answer(&mut self, l: usize, r: usize, lo: usize, hi: usize, p: usize) -> i32 {
         if l > r {
            return i32::MAX;
         } else if r - l == hi - lo {
            return self.st[p];
         }

         let mid = (lo + hi) / 2;

         self.push(p);

         let left = self.answer(l, r.min(mid), lo, mid, 2 * p);
         let right = self.answer(l.max(mid + 1), r, mid + 1, hi, 2 * p + 1);

         return left.min(right);
      }

      pub fn update(&mut self, x: i32, l: usize, r: usize) {
         self.apply(x, l, r, 0, self.n - 1, 1);
      }

      pub fn query(&mut self, l: usize, r: usize) -> i32 {
         self.answer(l, r, 0, self.n - 1, 1)
      }
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
   
   let n = sc.next::<usize>().ok().unwrap();

   let mut cnt: [i32; 2] = [0; 2];

   let mut st = (0..2).map(|_| SegTree::new(n)).collect::<Vec<_>>();

   for _ in 0..n {
      let mut points: [i32; 2] = [0; 2];

      let v = sc.next::<usize>().ok().unwrap() - 1;
      let t = sc.next::<usize>().ok().unwrap() - 1;

      cnt[t] += 1;

      st[t].update(-1, 0, v);
      st[t ^ 1].update(1, 0, v);

      for i in 0..2 {
         points[i] += if cnt[i] > cnt[i ^ 1] { 1 } else { 0 };
         points[i] += if st[i].query(0, n - 1) < 0 { 1 } else { 0 };
         points[i] = if points[i] > 0 { 1 } else { 0 }; 
      }

      if points[0] == points[1] {
         writeln!(handle, "?").ok();
      } else if points[0] > 0 {
         writeln!(handle, ">").ok();
      } else {
         writeln!(handle, "<").ok();
      }
   }
}