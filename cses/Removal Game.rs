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


fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const MAXN: usize = 5000;
   const INF: i64 = 0x1000000000000;

   let n = sc.next::<usize>().ok().unwrap();

   let mut x = [0; MAXN];
   let mut dp = [[0; 2]; MAXN];
   let mut sum = 0;
   let mut cur_player = !n & 1;

   for i in 0..n {
      x[i] = sc.next::<i64>().ok().unwrap();
      sum += x[i];
   }

   for i in 0..n {
      dp[i][cur_player] = x[i];
   }

   for i in (1..n).rev() {
      cur_player ^= 1;

      let player = cur_player;
      let other_player = cur_player ^ 1;
      
      for j in 0..i {
         dp[j][player] = -INF;
      }

      for j in 0..i {
         dp[j][player] = dp[j][player].max(x[j] - dp[j + 1][other_player]);
      }

      for j in 0..i {
         dp[j][player] = dp[j][player].max(x[j + n - i] - dp[j][other_player]);
      }
   }

   let max_score = (sum + dp[0][0]) / 2;

   writeln!(handle, "{max_score}").ok();
 }