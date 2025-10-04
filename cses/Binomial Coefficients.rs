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
         self.buffer.push_back(String::from(""));
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const MOD: i64 = 1000000007;
   const MAXN: usize = 1000000;

   let mut fat = vec![0; MAXN + 1];

   fat[0] = 1;

   let fast_exp = |mut n, mut p| {
      let mut answer = 1;

      while p > 0 {
         if p & 1 == 1 {
            answer = answer * n % MOD;
         }

         n = n * n % MOD;
         p >>= 1;
      }

      answer
   };

   for i in 1..=MAXN {
      fat[i] = i as i64 * fat[i - 1] % MOD;
   }

   let cnk = |n, k| {
      fat[n] * fast_exp(fat[k] * fat[n - k] % MOD, MOD - 2) % MOD
   };

   let n = sc.next::<usize>().ok().unwrap();

   for _ in 0..n {
      let n = sc.next::<usize>().ok().unwrap();
      let k = sc.next::<usize>().ok().unwrap();

      writeln!(handle, "{}", cnk(n, k)).ok();
   }
 }
