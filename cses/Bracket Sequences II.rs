#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::usize;

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

   const MOD: i64 = 1_000_000_007;

   let mut n = sc.next::<usize>().ok().unwrap();

   let str = sc.next::<String>().ok().unwrap().chars().collect::<Vec<_>>();

   if n & 1 == 1 {
      writeln!(handle, "0").ok();
      return;
   }

   let mut prefix = 0;

   for ch in str.iter() {
      if *ch == '(' {
         prefix += 1;
      } else {
         prefix -= 1;
         
         if prefix < 0 {
            writeln!(handle, "0").ok();
            return;
         }
      }
   }

   if prefix > n as i32 / 2 {
      writeln!(handle, "0").ok();
      return;
   }

   let mut fat = vec![0; 2 * n + 1];
   let mut inv = vec![0; 2 * n + 1];
   let mut inv_fat = vec![0; 2 * n + 1];

   for i in 0..2 {
      fat[i] = 1;
      inv[i] = 1;
      inv_fat[i] = 1;
   }

   for i in 2..=2*n {
      fat[i] = i as i64 * fat[i - 1] % MOD;
      inv[i] = (MOD - MOD / i as i64) * inv[MOD as usize % i] % MOD;
      inv_fat[i] = inv[i] * inv_fat[i - 1] % MOD;
   }

   let comb = move |n, k| {
      fat[n] * inv_fat[k] % MOD * inv_fat[n - k] % MOD
   };

   n -= str.len();

   let l = (n - prefix as usize) / 2;
   let u = prefix as usize + (n - prefix as usize) / 2;

   if l == 0 {
      writeln!(handle, "1").ok();
      return;
   }

   let answer = (comb(l + u, l) - comb(l + u, l - 1) + MOD) % MOD;

   writeln!(handle, "{answer}").ok();
 }
