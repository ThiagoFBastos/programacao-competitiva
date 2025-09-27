#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::cmp::Ordering;

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

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let m = sc.next::<usize>().ok().unwrap();
   let k = sc.next::<usize>().ok().unwrap();

   let mut a = (0..n).map(|_| sc.next::<i32>().ok().unwrap()).collect::<Vec<_>>();
   let mut b = (0..m).map(|_| sc.next::<i32>().ok().unwrap()).collect::<Vec<_>>();

   a.sort();
   b.sort();

   let mut j = 0;
   let mut count = 0;

   for i in 0..n {

      if j >= m {
         break;
      }

      let (Ok(mut pos) | Err(mut pos)) = b[j..m].binary_search_by(|candidate| match candidate.cmp(&(a[i] - k as i32)) {
         Ordering::Equal => Ordering::Greater,
         ord => ord
      });

      pos += j;

      if pos < m && b[pos] <= a[i] + k as i32 {
         count += 1;
         j = pos + 1;
      }
   }
   
   writeln!(handle, "{}", count).ok();
 }