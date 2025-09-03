#![allow(unused_imports)]
use std::collections::VecDeque;
use std::io::Write;
use std::ops::{Add, AddAssign, Sub};
 
struct Scanner {
   buffer : VecDeque<String>
}
 
impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new()
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> T {
 
      if self.buffer.is_empty() {
         let mut input = String::new();
         
         std::io::stdin().read_line(&mut input).ok();
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      front.parse::<T>().ok().unwrap()
   }
}

#[derive(Copy, Clone)]
struct Node<T> {
   sum: T,
   prefix: T,
   suffix: T,
   max_sum: T
}

impl<T: Copy + Ord + Add<Output = T>> Node<T> {

   fn new(value: T) -> Self {

      Self {
         sum: value,
         prefix: value,
         suffix: value,
         max_sum: value
      }
   }

   fn merge(&self, other: &Node<T>) -> Self {
      
      Self {
         sum: self.sum + other.sum,
         prefix: self.prefix.max(self.sum + other.prefix),
         suffix: other.suffix.max(self.suffix + other.sum),
         max_sum: self.max_sum.max(other.max_sum).max(self.suffix + other.prefix)
      }
   }
}

struct SegTree<T> {
   node: Vec<Node<T>>,
   len: usize
}

impl<T: Copy + Default + Ord + Add<Output = T>> SegTree<T> {

   fn build(&mut self, data: &Vec<T>, l: usize, r: usize, p: usize) {

      if l == r {
         self.node[p] = Node::new(data[l]);
         return;
      }

      let mid = (l + r) >> 1;

      self.build(data, l, mid, p << 1);
      self.build(data, mid + 1, r, (p << 1) | 1);

      self.node[p] = self.node[p << 1].merge(&self.node[(p << 1) | 1]);
   }

   fn new(data: &Vec<T>) -> Self {
      let n = data.len();

      let mut st = Self {
         node: vec![Node::new(T::default()); 4 * n],
         len: n
      };

      st.build(data, 0, n - 1, 1);

      st
   }

   fn query(&self, l: usize, r: usize, lo: usize, hi: usize, p: usize) -> Node<T> {
      
      if l <= lo && hi <= r {
         return self.node[p];
      }

      let mid = (lo + hi) >> 1;

      if l <= mid && r > mid {
         let left = self.query(l, r, lo, mid, p << 1);
         let right = self.query(l, r, mid + 1, hi, (p << 1) | 1);

         return left.merge(&right);
      } else if r <= mid {
         return self.query(l, r, lo, mid, p << 1);
      } else {
         return self.query(l, r, mid + 1, hi, (p << 1) | 1);
      }
   }

   fn max_sum(&self, l: usize, r: usize) -> T {
      self.query(l, r, 0, self.len - 1, 1).max_sum
   }

   fn update(&mut self, k: usize, x: T, lo: usize, hi: usize, p: usize) {

      if lo == hi {
         self.node[p] = Node::new(x);
         return;
      }

      let mid = (lo + hi) >> 1;

      if k <= mid {
         self.update(k, x, lo, mid, p << 1);
      } else {
         self.update(k, x, mid + 1, hi, (p << 1) | 1);
      }

      self.node[p] = self.node[p << 1].merge(&self.node[(p << 1) | 1]);
   }

   fn change(&mut self, k: usize, x: T) {
      self.update(k, x, 0, self.len - 1, 1);
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
 
   let n = sc.next::<usize>();

   let arr = (0..n).map(|_| sc.next::<i32>()).collect::<Vec<i32>>();

   let mut st = SegTree::new(&arr);

   let q = sc.next::<usize>();

   for _ in 0..q {

     let query_type = sc.next::<u8>();

     if query_type == 0 {
      let pos  = sc.next::<usize>() - 1;
      let value = sc.next::<i32>();

      st.change(pos, value);
     } else {
      let l = sc.next::<usize>() - 1;
      let r = sc.next::<usize>() - 1;

      writeln!(handle, "{}", st.max_sum(l, r)).ok();
     }
   }
}
