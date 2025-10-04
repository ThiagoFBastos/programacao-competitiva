#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, HashMap};
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

struct XorTrie {
   container: Vec<Vec<Option<(usize, i32)>>>
}

impl XorTrie {

   fn new() -> Self {

      Self {
         container: vec![vec![None, None]]
      }
   }

   fn insert(&mut self, value: i32) {

      if self.exists(value) {
         return;
      }
      
      let mut cur = 0;

      for i in (0..30).rev() {
         let bit = (value >> i) & 1;

         if self.container[cur][bit as usize].is_none() {
            let length = self.container.len();

            self.container.push(vec![None, None]);

            self.container[cur][bit as usize] = Some((length, 0));
         }

         let (no, count) = self.container[cur][bit as usize].unwrap();

         self.container[cur][bit as usize] = Some((no, count + 1));
         cur = no;
      }
   }

   fn exists(&self, value: i32) -> bool {
      let mut cur = 0;

      for i in (0..30).rev() {
         let bit = (value >> i) & 1;

         if self.container[cur][bit as usize].is_none() {
            return false;
         }

         cur = self.container[cur][bit as usize].unwrap().0;
      }

      true
   }

   fn remove(&mut self, value: i32) {
      let mut cur = 0;

      if !self.exists(value) {
         return;
      }

      for i in (0..30).rev() {
         let bit = (value >> i) & 1;

         let (no, count) = self.container[cur][bit as usize].unwrap();

         if count == 1 {
            self.container[cur][bit as usize] = None;
         } else {
            self.container[cur][bit as usize] = Some((no, count - 1));
         }

         cur = no;
      }
   }

   fn min_xor(&self, value: i32) -> i32 {
      let mut cur = 0;
      let mut answer = 0;

      for i in (0..30).rev() {
         let bit = (value >> i) & 1;

         if !self.container[cur][bit as usize].is_none() {
            cur = self.container[cur][bit as usize].unwrap().0;
         } else if !self.container[cur][(bit ^ 1) as usize].is_none() {
            answer |= 1 << i;
            cur = self.container[cur][(bit ^ 1) as usize].unwrap().0;
         } else {
            panic!();
         }
      }

      answer
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let q = sc.next::<usize>().ok().unwrap();

   let mut trie = XorTrie::new();

   for _ in 0..q {
      let t = sc.next::<u8>().ok().unwrap();
      let x = sc.next::<i32>().ok().unwrap();

      if t == 0 {
         trie.insert(x);
      } else if t == 1 {
         trie.remove(x);
      } else {
         writeln!(handle, "{}", trie.min_xor(x)).ok();
      }
   }
 }
