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

fn bin_exp(mut n: i64, mut p: i64, modulo: i64) -> i64 {
   let mut answer = 1;

   while p > 0 {
      if p & 1 == 1 {
         answer = answer * n % modulo;
      }

      n = n * n % modulo;
      p >>= 1;
   }

   answer
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const MOD: i64 = 1_000_000_007;

   let str = sc.next::<String>().ok().unwrap().chars().collect::<Vec<_>>();

   let n = str.len();

   let mut count = [0; 26];

   let mut fat = vec![0; n + 1];

   fat[0] = 1_i64;

   for i in 1..=n {
      fat[i] = fat[i - 1] * i as i64 % MOD;
   }

   for c in str.iter() {
      count[*c as usize - 'a' as usize] += 1;
   }

   let mut combinations = 1;

   for i in 0..26 {
      combinations = combinations * fat[count[i]] % MOD;
   }

   let answer = fat[n] * bin_exp(combinations, MOD - 2, MOD) % MOD;

   writeln!(handle, "{}", answer).ok();
 }
