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
   
   fn next<T : std::str::FromStr>(&mut self) -> T {
 
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

struct BIT<T> {
   data: Vec<T>,
   len: usize
}

impl<T: Copy + Default + AddAssign + Add<Output = T> + Sub<Output = T>> BIT<T> {

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
   let q = sc.next::<usize>();

   let mut bit: BIT<i32> = BIT::new(n);

   for _ in 0..q {
      let query = sc.next::<u8>();

      if query == 1 {
         let pos = sc.next::<i32>();
         let value = sc.next::<i32>();

         bit.update(pos, value);
      } else {

         let l1 = sc.next::<i32>();
         let r1 = sc.next::<i32>();
         let l2 = sc.next::<i32>();
         let r2 = sc.next::<i32>();

         if r1.min(r2) < l1.max(l2) {
            let sum = bit.query_range(l1, r1) + bit.query_range(l2, r2);

            writeln!(handle, "{}", sum).ok();
         } else {
            let l = l1.min(l2);
            let r = r1.max(r2);

            writeln!(handle, "{}", bit.query_range(l, r)).ok();
         }
      }
   }
}
