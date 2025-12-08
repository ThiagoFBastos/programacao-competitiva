#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::Ordering;
use std::collections::{VecDeque};
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

   let mut sc  = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();

   let mut projects = Vec::with_capacity(n);
   let mut dp = vec![0; n];

   for _ in 0..n {
      let a = sc.next::<i32>().ok().unwrap();
      let b = sc.next::<i32>().unwrap();
      let p = sc.next::<i64>().ok().unwrap();

      projects.push((a, b, p));
   }

   projects.sort_by_key(|element| element.1);
   
   dp[0] = projects[0].2;

   for i in 1..n {
      let pos = projects.binary_search_by(|element| match  element.1.cmp(&(projects[i].0 - 1)) {
         Ordering::Equal => Ordering::Less,
         ord => ord
      }).unwrap_err() as i32 - 1;

      if pos >= 0 {
         dp[i] = projects[i].2 + dp[pos as usize];
      } else {
         dp[i] = projects[i].2;
      }

      dp[i] = dp[i].max(dp[i - 1]);
   }

   writeln!(handle, "{}", dp.last().unwrap()).ok();
}
