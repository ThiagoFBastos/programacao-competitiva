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

macro_rules! int {
    ( $x:expr ) => {
         if($x) { 1 } else { 0 }
    };
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const INF: i32 = 1_000_000_000;

   let mut s = sc.next::<String>().unwrap().chars().collect::<Vec<_>>();
   let mut t = sc.next::<String>().unwrap().chars().collect::<Vec<_>>();

   let n = s.len();
   let m = t.len();

   s.push('\0');
   t.push('\0');

   let mut dp = vec![vec![INF; m + 2]; n + 2];

   dp[0][0] = 0;

   for i in 0..=n {
      for j in 0..=m {
        dp[i + 1][j + 1] = dp[i + 1][j + 1].min(dp[i][j] + int!(s[i] != t[j]));
        dp[i + 1][j] = dp[i + 1][j].min(1 + dp[i][j]);
			  dp[i][j + 1] = dp[i][j + 1].min(1 + dp[i][j]);
      }
   }

   writeln!(handle, "{}", dp[n][m]).ok();
 }
