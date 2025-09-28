#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, BTreeMap, BTreeSet};
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

trait OrderedSet<T> {
   fn new() -> Self;
   fn insert(&mut self, value: T);
   fn lower_bound(&self, value: T) -> Option<&T>;
   fn upper_bound(&self, value: T) -> Option<&T>;
   fn previous(&self, value: T) -> Option<&T>;
   fn remove(&mut self, value: T);
   fn first(&self) -> Option<&T>;
   fn last(&self) -> Option<&T>;
}

struct Set<T> {
   container: BTreeSet<T>
}

impl<T: Ord> OrderedSet<T> for Set<T> {

   fn new() -> Self {
      Self {
         container: BTreeSet::new()
      }
   }

   fn insert(&mut self, value: T) {
      self.container.insert(value);
   }

   fn lower_bound(&self, value: T) -> Option<&T> {
      let mut range = self.container.range((Included(value), Unbounded));
      range.next()
   }

   fn upper_bound(&self, value: T) -> Option<&T> {
      let mut range = self.container.range((Excluded(value), Unbounded));
      range.next()
   }

   fn previous(&self, value: T) -> Option<&T> {
      let mut range = self.container.range((Unbounded, Excluded(value)));
      range.next_back()
   }

   fn remove(&mut self, value: T) {
      self.container.remove(&value);
   }

   fn first(&self) -> Option<&T> {
      self.container.first()
   }

   fn last(&self) -> Option<&T> {
      self.container.last()
   }
}
struct Multiset<T> {
   container: BTreeMap<T, usize>
}

impl<T: Ord> OrderedSet<T> for Multiset<T> {

   fn new() -> Self {
      Self {
         container: BTreeMap::new()
      }
   }

   fn insert(&mut self, value: T) {
      let count = *self.container.get(&value).unwrap_or(&0);
      self.container.insert(value, count + 1);
   }

   fn lower_bound(&self, value: T) -> Option<&T> {
      let mut range = self.container.range((Included(value), Unbounded));
      
      let it = range.next();

      if it.is_none() {
         return None;
      }

      let (result, _) = it.unwrap();

      Some(result)
   }

   fn upper_bound(&self, value: T) -> Option<&T> {
      let mut range = self.container.range((Excluded(value), Unbounded));
      
      let it = range.next();

      if it.is_none() {
         return None;
      }

      let (result, _) = it.unwrap();

      Some(result)
   }

   fn previous(&self, value: T) -> Option<&T> {
      let mut range = self.container.range((Unbounded, Excluded(value)));
      let it = range.next_back();

      if it.is_none() {
         return None;
      }

      Some(it.unwrap().0)
   }

   fn remove(&mut self, value: T) {
      let count = *self.container.get(&value).unwrap_or(&0);

      if count == 1 {
         self.container.remove(&value);
      } else if count > 1 {
         self.container.insert(value, count - 1);
      }
   }

   fn first(&self) -> Option<&T> {
      let first = self.container.first_key_value();

      if first.is_none() {
         return None;
      }

      Some(first.unwrap().0)
   }

   fn last(&self) -> Option<&T> {
      let last = self.container.last_key_value();

      if last.is_none() {
         return None;
      }

      Some(last.unwrap().0)
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let x = sc.next::<i32>().ok().unwrap();
   let n = sc.next::<usize>().ok().unwrap();

   let mut positions = Set::new();
   let mut longest = Multiset::new();

   positions.insert(0);
   positions.insert(x);
   longest.insert(x);

   for _ in 0..n {

      let pos = sc.next::<i32>().ok().unwrap();

      let high = *positions.upper_bound(pos).unwrap();
      let low = *positions.previous(pos).unwrap();

      longest.remove(high - low);
      longest.insert(pos - low);
      longest.insert(high - pos);
      positions.insert(pos);

      write!(handle, "{} ", longest.last().unwrap()).ok();
   }

   write!(handle, "\n").ok();
 }