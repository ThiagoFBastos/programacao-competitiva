#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::Write;
use std::ops::Add;
 
struct Scanner {
   buffer: VecDeque<String>
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

trait Min {

   fn min_value() -> Self;
}

impl Min for i32 {

   fn min_value() -> Self {
      i32::MIN
   }
}

#[derive(Clone, Copy)]
struct Node<T> {
   max_value: T,
   max_sum: T
}

impl<T: Copy + Ord + Min + Add<Output = T>> Node<T> {

   fn new(value: T) -> Self {

      Self {
         max_value: value,
         max_sum: T::min_value()
      }
   }

   fn merge(&self, other: &Node<T>) -> Self {

      Self {
         max_value: self.max_value.max(other.max_value),
         max_sum: self.max_sum.max(other.max_sum).max(self.max_value + other.max_value)
      }
   }
}

trait Range<T> {

   fn new(arr: &[T]) -> Self;

   fn build(&mut self, arr: &[T], lo: usize, hi: usize, p: usize);

   fn query(&self, l: usize, r: usize, lo: usize, hi: usize, p: usize) -> Node<T>;

   fn max_sum(&self, l: usize, r: usize) -> T;

   fn update(&mut self, k: usize, value: T, lo: usize, hi: usize, p: usize);

   fn change(&mut self, k: usize, value: T);
}

struct SegTree<T> {

   data: Vec<Node<T>>,
   len: usize
}

impl<T: Default + Copy + Ord + Min + Add<Output = T>> Range<T> for SegTree<T> {
   fn new(arr: &[T]) -> Self {

      let n = arr.len();

      let mut segtree = Self {
         data: vec![Node::new(T::default()); 4 * n],
         len: n
      };

      segtree.build(arr, 0, n - 1, 1);

      return segtree;
   }

   fn build(&mut self, arr: &[T], lo: usize, hi: usize, p: usize) {

      if lo == hi {
         self.data[p] = Node::new(arr[lo]);
         return;
      }

      let mid = (lo + hi) >> 1;

      self.build(arr, lo, mid, p << 1);
      self.build(arr, mid + 1, hi, (p << 1) | 1);

      self.data[p] = self.data[p << 1].merge(&self.data[(p << 1) | 1]);
   }

   fn query(&self, l: usize, r: usize, lo: usize, hi: usize, p: usize) -> Node<T> {

      if lo >= l && hi <= r {
         return self.data[p];
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

   fn update(&mut self, k: usize, value: T, lo: usize, hi: usize, p: usize) {

      if lo == hi {
         self.data[p] = Node::new(value);
         return;
      }

      let mid = (lo + hi) >> 1;

      if k <= mid {
         self.update(k, value, lo, mid, p << 1);
      } else {
         self.update(k, value, mid + 1, hi, (p << 1) | 1);
      }

      self.data[p] = self.data[p << 1].merge(&self.data[(p << 1) | 1]);
   }

   fn change(&mut self, k: usize, value: T) {
      self.update(k, value, 0, self.len - 1, 1);
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
 
   let n = sc.next::<usize>();

   let arr: Vec<_> = (0..n).map(|_| sc.next::<i32>()).collect();

   let mut segtree = SegTree::new(&arr);

   let q = sc.next::<usize>();

   for _ in 0..q {

      let query = sc.next::<char>();

      if query == 'U' {

         let pos = sc.next::<usize>() - 1;
         let value = sc.next::<i32>();

         segtree.change(pos, value);
      } else {

         let l = sc.next::<usize>() - 1;
         let r = sc.next::<usize>() - 1;

         writeln!(handle, "{}", segtree.max_sum(l, r)).ok();
      }
   }
}
