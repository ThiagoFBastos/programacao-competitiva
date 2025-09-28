#![allow(unused_imports)]
#![allow(dead_code)]
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
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn minimum_coins(coins: & mut [usize], target: usize) -> Option<i32> {
   let n = coins.len();
   const INF: i32 = 10_000_000;

   let mut dp = vec![INF; target + 1];

   coins.sort();

   dp[0] = 0;
   
   for i in 1..=target {
      for j in 0..n{
         if i < coins[j] {
            break;
         }
         dp[i] = dp[i].min(1 + dp[i - coins[j]]);
      }
   }

   if dp[target] == INF {
      return None;
   }

   Some(dp[target])
}

#[cfg(test)]
mod unit_tests {
   use super::*;

   #[test]
   fn test_sample_case() {
      let target = 11;
      let mut coins = vec![1, 5, 7];

      assert_eq!(minimum_coins(&mut coins, target), Some(3));
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let target = sc.next::<usize>().ok().unwrap();

   let mut coins = (0..n).map(|_| sc.next::<usize>().ok().unwrap()).collect::<Vec<_>>();

   let result = minimum_coins(&mut coins, target);

   writeln!(handle, "{}", result.unwrap_or(-1)).ok();
 }