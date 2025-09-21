#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::ops::{BitAnd, Mul, Rem, ShrAssign};

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
               return Err(Error::new(ErrorKind::UnexpectedEof, "End Of Line"));
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

trait Constants {
   fn zero() -> Self;
   fn one() -> Self;
}

impl Constants for i64 {
   fn zero() -> Self {
      return 0;
   }

   fn one() -> Self {
       return 1;
   }
}

fn fast_exp<T: Copy + Mul<Output = T> + Constants + Ord + ShrAssign + BitAnd<Output = T> + Rem<Output = T>>(mut a: T, mut p: T, modulo: T) -> T {
   let mut result = T::one();

   while p > T::zero() {
      if p & T::one() == T::one() {
         result = result * a % modulo;
      }

      a = a * a % modulo;

      p >>= T::one();
   }

   result
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
   
   const MOD: i64 = 1_000_000_007;

   let k = sc.next::<usize>().ok().unwrap();
   let n = sc.next::<usize>().ok().unwrap();

   let mut ans = fast_exp(n as i64, k as i64, MOD);

   let mut fac = vec![1; n + 1];
   let mut inv = vec![1; n + 1];
   let mut inv_fac = vec![1; n + 1];

   inv[0] = 0;

   for i in 2..=n {
      fac[i] = i as i64 * fac[i - 1] % MOD;
      inv[i] = (MOD - MOD / i as i64) * inv[(MOD % i as i64) as usize] % MOD;
      inv_fac[i] = inv_fac[i - 1] * inv[i] % MOD;
   }

   let cnk = |n, k| {
      fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD
   };

   for i in 1..n {
      let combinations = fast_exp((n - i) as i64, k as i64, MOD) * cnk(n as usize, i as usize) % MOD;

      if i & 1 == 1 {
         ans = (ans - combinations + MOD) % MOD;
      } else {
         ans = (ans + combinations) % MOD;
      }
   }

   writeln!(handle, "{}", ans).ok();
}