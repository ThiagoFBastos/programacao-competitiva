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
  
   let n = sc.next::<usize>().ok().unwrap();

   let mut frequency = vec![0; n + 1];

   let code = (0..n-2).map(|_| sc.next::<usize>().ok().unwrap()).collect::<Vec<_>>();

   let mut pq = BinaryHeap::new();

   for i in 0..code.len() {
      frequency[code[i]] += 1;
   }

   for v in 1..=n {
      if frequency[v] == 0 {
         pq.push(Reverse(v));
      }
   }

   for i in 0..code.len() {
      let v = pq.pop().unwrap().0;

      writeln!(handle, "{} {}", v, code[i]).ok();

      frequency[code[i]] -= 1;

      if frequency[code[i]] == 0 {
         pq.push(Reverse(code[i]));
      }
   }

   let u = pq.pop().unwrap().0;
   let v = pq.pop().unwrap().0;

   writeln!(handle, "{} {}", u, v).ok();
}
