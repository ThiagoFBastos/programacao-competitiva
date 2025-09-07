#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::Write;

use crate::data_structures::{SegTree, Combinator, Function};
 
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

mod data_structures {
   use std::ops::BitOr;
   use std::marker::PhantomData;

   pub trait Combinator {

      fn combine<T: BitOr<Output = T>>(left: T, right: T) -> T;
   }
   
   pub struct Function;

   impl Combinator for Function {

      fn combine<T: BitOr<Output = T>>(left: T, right: T) -> T {
         left | right
      }
   }

   pub struct SegTree<T, Fn> {
      data: Vec<T>,
      len: usize,
      _combinator: PhantomData<Fn>
   }

   impl<T: BitOr<Output = T> + Copy + Default, Fn: Combinator> SegTree<T, Fn> {

      pub fn new(data: &[T]) -> Self {

         let n = data.len();

         let mut segtree = Self {
            data: vec![T::default(); 4 * n],
            len: n,
            _combinator: PhantomData
         };

         segtree.build(data, 0, n - 1, 1);

         segtree
      }

      fn build(&mut self, data: &[T], lo: usize, hi: usize, p: usize) {

         if lo == hi {
            self.data[p] = data[lo];
            return;
         }

         let mid = (lo + hi) / 2;

         self.build(data, lo, mid, 2 * p);
         self.build(data, mid + 1, hi, 2 * p + 1);

         self.data[p] = Fn::combine(self.data[2 * p], self.data[2 * p + 1]);
      }

      fn _update(&mut self, k: usize, value: T, lo: usize, hi: usize, p: usize) {

         if lo == hi {
            self.data[p] = value;
            return;
         }

         let mid = (lo + hi) / 2;

         if k <= mid {
            self._update(k, value, lo, mid, 2 * p);
         } else {
            self._update(k, value, mid + 1, hi, 2 * p + 1);
         }

         self.data[p] = Fn::combine(self.data[2 * p], self.data[2 * p + 1]);
      }

      fn _query(&self, l: usize, r: usize, lo: usize, hi: usize, p: usize) -> T {

         if r < lo || l > hi {
            return T::default();
         } else if lo >= l && hi <= r {
            return self.data[p];
         }

         let mid = (lo + hi) / 2;

         let left = self._query(l, r, lo, mid, 2 * p);
         let right = self._query(l, r, mid + 1, hi, 2 * p + 1);

         Fn::combine(left, right)
      }

      pub fn update(&mut self, k: usize, value: T) {
         self._update(k, value, 0, self.len - 1, 1);
      }

      pub fn query(&self, l: usize, r: usize) -> T {
         self._query(l, r, 0, self.len - 1, 1)
      }
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let arr = sc.next::<String>().chars()
                                .map(|c| 1 << ((c as u8) - ('a' as u8)))
                                .collect::<Vec<i32>>();

   let q = sc.next::<usize>();

   let mut st: SegTree<i32, Function> =SegTree::new(&arr);

   for _  in 0..q {

      let query = sc.next::<u8>();

      if query == 1 {
         let pos = sc.next::<usize>() - 1;
         let c = sc.next::<char>();

         let bitmask = 1 << ((c as u8) - ('a' as u8));

         st.update(pos, bitmask);
      } else {

         let l = sc.next::<usize>() - 1;
         let r = sc.next::<usize>() - 1;

         let answer = st.query(l, r);

         writeln!(handle, "{}", answer.count_ones()).ok();
      }
   }
}
