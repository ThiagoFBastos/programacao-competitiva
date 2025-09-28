#![allow(unused_imports)]
use std::collections::{VecDeque, BTreeMap};
use std::io::{self, Error, ErrorKind, Write};

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

macro_rules! int {
    ( $x:expr ) => {
         if($x) { 1 } else { 0 }
    };
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();

   let mut left = Vec::with_capacity(n);
   let mut right = Vec::with_capacity(n);

   for i in 0..n {
      let l = sc.next::<i32>().ok().unwrap();
      let r = sc.next::<i32>().ok().unwrap();

      left.push((l, -r, i));
      right.push((r, -l, i));
   }

   left.sort();
   right.sort();

   let mut i = 0;
   let mut j = 0;
   let mut max_right = 0;
   let mut multiset = BTreeMap::new();
   let mut a = vec![0; n];
   let mut b = vec![0; n];

   while i < n {

      let (ll, rl, pos_l) = left[i];
      let (rr, lr, pos_r) = right[j];

      if ll <= rr {
         a[pos_l] = int!(!multiset.is_empty() && *multiset.last_key_value().unwrap().0 >= -rl);
         multiset.insert(-rl, *multiset.get(&(-rl)).unwrap_or(&0) + 1);
         i += 1;
      } else {
         b[pos_r] = int!(max_right >= -lr);
         max_right = max_right.max(-lr);

         if let Some(count) = multiset.get(&rr) {
            if *count == 1 {
               multiset.remove(&rr);
            } else {
               multiset.insert(rr, *count - 1);
            }
         }

         j += 1;
      }
   }

   while j < n {
      let (_, lr, pos_r) = right[j];
      b[pos_r] = int!(max_right >= -lr);
      max_right = max_right.max(-lr);
      j += 1;
   }

   for x in b.iter() {
      write!(handle, "{} ", x).ok();
   }

   write!(handle, "\n").ok();

   for x in a.iter() {
      write!(handle, "{} ", x).ok();
   }
   
   write!(handle, "\n").ok();
 }