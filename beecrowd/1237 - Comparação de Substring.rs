#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::*;
use std::collections::*;

struct Scanner {
   buffer : VecDeque<String>,
   eof: bool
}
 
impl Scanner {
 
   fn new() -> Scanner {
      Scanner {
         buffer: VecDeque::new(),
         eof: false
      }
   }
   
   fn next<T : std::str::FromStr + Default >(&mut self) -> T {
 
      if self.buffer.len() == 0 {
         let mut input = String::new();
         
         match std::io::stdin().read_line(&mut input) {
            Ok(0) => self.eof = true,
            Ok(_) => {},
            Err(e) => panic!("panico {}", e)
         };

         for word in input.split_whitespace() {
            self.buffer.push_back(word.to_string())
         }
      }

      if self.eof {
         return T::default();
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      front.parse::<T>().ok().unwrap()
   }

   fn read_line(&mut self) -> String {
      let mut input = String::new();
         
      match std::io::stdin().read_line(&mut input) {
         Ok(0) => self.eof = true,
         Ok(_) => {},
         Err(e) => panic!("{}", e)
      };

      if input.ends_with('\n') {
         input.pop();
         if input.ends_with('\r') {
            input.pop();
         }
      }

      return input;
   }

   fn is_eof(&self) -> bool {
      self.eof
   }
}

fn main() {

   let mut sc = Scanner::new();

   loop {
      let str1: String = sc.read_line();

      if sc.is_eof() {
         break;
      }

      let str2: String = sc.read_line();

      let n = str1.len();
      let m = str2.len();

      let mut dp = vec![vec![0; m + 1]; n + 1];

      let str1_chars = str1.chars().collect::<Vec<char>>();
      let str2_chars = str2.chars().collect::<Vec<char>>();
      let mut ans = i32::default();

      for i in 1..=n {
         for j in 1..=m {

            if str1_chars[i - 1] == str2_chars[j - 1] {
               dp[i][j] = 1 + dp[i - 1][j - 1];
            }

            if ans < dp[i][j] {
               ans = dp[i][j];
            }
         }
      }

      println!("{}", ans);
   }
}