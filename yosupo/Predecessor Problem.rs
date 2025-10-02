#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, BTreeSet};
use std::io::{self, Error, ErrorKind, Write};
use std::ops::Bound::*;

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

struct Set<T> {
   container: BTreeSet<T>
}

impl<T: Ord> Set<T> {


   fn new() -> Self {

      Self {
         container: BTreeSet::new()
      }
   }

   fn insert(&mut self, value: T) {
      self.container.insert(value);
   }

   fn remove(&mut self, value: T) {
      self.container.remove(&value);
   }

   fn contains(&self, value: T) -> bool {
      self.container.contains(&value)
   }

   fn lower_bound(&self, value: T) -> Option<&T> {
      let mut range = self.container.range((Included(value), Unbounded));

      range.next()
   }

   fn higher_bound(&self, value: T) -> Option<&T> {
      let mut range = self.container.range((Unbounded, Included(value)));

      range.next_back()
   }
}


fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let mut set = Set::new();

   let n = sc.next::<usize>().ok().unwrap();
   let q = sc.next::<usize>().ok().unwrap();

   let state = sc.next::<String>().ok().unwrap().chars().collect::<Vec<_>>();

   for i in 0..n {
      if state[i] == '1' {
         set.insert(i as i32);
      }
   }

   for _ in 0..q {
      
      let t = sc.next::<u8>().ok().unwrap();
      let k = sc.next::<i32>().ok().unwrap();

      if t == 0 {
         set.insert(k);
      } else if t == 1 {
         set.remove(k);
      } else if t == 2 {
         writeln!(handle, "{}", if set.contains(k) { 1 } else { 0 }).ok(); 
      } else if t == 3 {
         let result = set.lower_bound(k);
         writeln!(handle, "{}", if result.is_none() { &-1 } else { result.unwrap() }).ok();
      } else if t == 4 {
         let result = set.higher_bound(k);
         writeln!(handle, "{}", if result.is_none() { &-1 } else { result.unwrap() }).ok();
      } else {
         panic!("wrong option");
      }
   }
 }
