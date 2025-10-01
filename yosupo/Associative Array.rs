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
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

struct AssociativeArray<T, V> {
   container: BTreeMap<T, V>
}

impl<T: Ord, V> AssociativeArray<T, V> {

   fn new() -> Self {

      Self {
         container: BTreeMap::new()
      }
   }

   fn set(&mut self, key: T, value: V) {
      self.container.insert(key, value);
   }

   fn get(&self, key: T) -> Option<&V> {
      self.container.get(&key)
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let q = sc.next::<usize>().ok().unwrap();

   let mut array = AssociativeArray::new();

   for _ in 0..q {
      let t = sc.next::<u8>().ok().unwrap();
      let k = sc.next::<u64>().ok().unwrap();

      if t == 0 {
         let v = sc.next::<u64>().ok().unwrap();
         array.set(k, v);
      } else {
         writeln!(handle, "{}", array.get(k).unwrap_or(&0)).ok();
      }
   }
 }
