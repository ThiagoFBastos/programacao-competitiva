#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::Reverse;
use std::collections::{VecDeque, BinaryHeap};
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
         self.buffer.push_back("".to_string());
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);

   let mut sc = Scanner::new();

   let _ = sc.next::<i32>().unwrap();
   let n = sc.next::<usize>().unwrap();

   let mut pq = BinaryHeap::new();

   for _ in 0..n {
      pq.push(Reverse(sc.next::<i64>().unwrap()));
   }

   let mut answer = 0;

   while pq.len() > 1 {

      let a = pq.pop().unwrap().0;
      let b = pq.pop().unwrap().0;

      answer += a + b;
  
      pq.push(Reverse(a + b));
   }

   writeln!(handle, "{}", answer).ok();
}
