#![allow(unused_imports)]
#![allow(dead_code)]
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
 
      if self.buffer.is_empty() {
         self.buffer.push_back(String::from(""));
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

struct Multiset<T> {
   container: BTreeMap<T, u32>
}

impl<T: Ord> Multiset<T> {

   fn new() -> Self {

      Self {
         container: BTreeMap::new()
      }
   }

   fn insert(&mut self, value: T) {
      let count = *self.container.get(&value).unwrap_or(&0);
      self.container.insert(value, count + 1);
   }

   fn remove(&mut self, value: T) {
      let count = *self.container.get(&value).unwrap_or(&0);

      if count <= 1 {
         self.container.remove(&value);
      } else {
         self.container.insert(value, count - 1);
      }
   }

   fn first(&self) -> Option<&T> {
      let key = self.container.first_key_value();
      
      if key.is_none() {
         return None;
      }

      Some(key.unwrap().0)
   }

   fn last(&self) -> Option<&T> {
      let key = self.container.last_key_value();
      
      if key.is_none() {
         return None;
      }

      Some(key.unwrap().0)
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let q = sc.next::<usize>().ok().unwrap();

   let mut set = Multiset::new();

   (0..n).for_each(|_| {
      let value = sc.next::<i32>().ok().unwrap();
      set.insert(value);
   });

   if n == 0 {
      sc.next::<String>().ok();
   }

   for _ in 0..q {
      let t = sc.next::<u8>().ok().unwrap();
      
      if t == 0 {
         let x = sc.next::<i32>().ok().unwrap();
         set.insert(x);
      } else if t == 1 {
         let min = *set.first().unwrap();
         writeln!(handle, "{min}").ok();
         set.remove(min);
      } else {
         let max = *set.last().unwrap();
         writeln!(handle, "{max}").ok();
         set.remove(max);
      }
   }
 }
