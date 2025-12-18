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

   let n = sc.next::<usize>().unwrap();

   let pairs = (0..2*n).map(|_| sc.next::<i32>().unwrap()).collect::<Vec<_>>();

   let mut second_position = BTreeMap::new();
   let mut dp = vec![(0, 0); 2 * n + 1];

   for (i, val) in pairs.iter().enumerate() {
      second_position.insert(*val, i);
   }

   for (i, val) in pairs.iter().enumerate().rev() {
      let position = *second_position.get(val).unwrap();

      if i == position {
         dp[i] = dp[i + 1];
      } else {
         dp[i] = (dp[position].0 + 1, dp[position].1 - (position - i) as i64);
      }

      dp[i] = dp[i].max(dp[i + 1]);
   }

   let (count, price) = dp[0];

   writeln!(handle, "{} {}", count, -price).ok();
 }
