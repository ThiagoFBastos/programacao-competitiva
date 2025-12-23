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

      if self.buffer.is_empty() {
         self.buffer.push_back("".to_string());
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

const INF: i64 = 100_000_000_000_000_000;

fn divide_and_conquer(k: usize, dp: &mut Vec<Vec<i64>>, pre: &Vec<i64>, lo: usize, hi: usize, l: usize, r: usize) {

   let mid = (l + r) / 2;

   let mut best_value = (INF, 0);

   for i in lo..mid.min(hi + 1) {
      best_value = best_value.min((dp[k - 1][i] + (pre[mid] - pre[i]).pow(2), i));
   }

   let (value, pos) = best_value;

   dp[k][mid] = value;

   if mid > l {
      divide_and_conquer(k, dp, pre, lo, pos, l, mid - 1);
   }

   if mid < r {
      divide_and_conquer(k, dp, pre, pos, hi, mid + 1, r);
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let k = sc.next::<usize>().unwrap();

   let mut dp = vec![vec![INF; n + 1]; k + 1];

   let mut pre = Vec::with_capacity(n + 1);

   pre.push(0);

   for i in 1..=n {
      pre.push(sc.next::<i64>().unwrap() + pre[i - 1]);
   }

   dp[0][0] = 0;

   for i in 1..=k {
      divide_and_conquer(i, &mut dp, &pre, 0, n, 0, n);
   }

   writeln!(handle, "{}", dp[k][n]).ok();
 }
