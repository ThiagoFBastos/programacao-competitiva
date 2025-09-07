#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::Write;
use std::ops::{Add, AddAssign, Sub};
use std::process::Output;
 
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

trait Range<T> {

   fn new(n: usize) -> Self;

   fn update(&mut self, k: i32, value: T);

   fn query(&self, k: i32) -> T;

   fn query_range(&self, l: i32, r: i32) -> T;
}

struct Fenwick<T> {
   data: Vec<T>,
   len: usize
}

impl<T: Copy + Default + AddAssign + Add<Output = T> + Sub<Output = T>> Range<T> for Fenwick<T> {

   fn new(n: usize) -> Self {

      Self {
         data: vec![T::default(); n + 1],
         len: n
      }
   }

   fn update(&mut self, mut k: i32, value: T) {

      while k as usize <= self.len {
         self.data[k as usize] += value;
         k += k & -k;
      }
   }

   fn query(&self, mut k: i32) -> T {
      let mut answer = T::default();

      while k > 0 {
         answer += self.data[k as usize];
         k -= k & -k;
      }

      answer
   }

   fn query_range(&self, l: i32, r: i32) -> T {
      self.query(r) - self.query(l - 1)
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
 
   let n = sc.next::<usize>();

   let mut arr: Vec<_> = (0..n).map(|i| (sc.next::<i32>(), i)).collect();

   arr.sort();

   let mut permutation = vec![0; n];

   (0..n).for_each(|i| { permutation[arr[i].1] = i + 1 });

   let mut ft1 = Fenwick::new(n);
   let mut ft2 = Fenwick::new(n);
   let mut inversions = i64::default();

   for i in 0..n {
      ft1.update(permutation[i] as i32, 1 as i64);
      ft2.update(permutation[i] as i32, ft1.query_range((permutation[i] + 1) as i32, n as i32));
      inversions += ft2.query_range((permutation[i] + 1) as i32, n as i32);
   }

   writeln!(handle, "{}", inversions).ok();
}
