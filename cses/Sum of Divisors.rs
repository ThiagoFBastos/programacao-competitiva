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

   const MOD: i64 = 1_000_000_007;
   
   let sum_mod = |a, b| {
      const INV_2: i64 = (MOD + 1) / 2;

      let p = (b - a + 1) % MOD;
      let q = (a + b) % MOD;

      return p * q % MOD * INV_2 % MOD;
   };

   let n = sc.next::<i64>().ok().unwrap();

   let k = (n as f64).sqrt() as usize;

   let mut ans = 0;

   let mut r = Vec::new();

   r.push(n + 1);

   for i in 1..=k {
      let mut lo = 1;
      let mut hi = n;

      while lo < hi {

         let mid = (lo + hi) / 2;

         if n / mid > i as i64 {
            lo = mid + 1;
         } else {
            hi = mid;
         }
      }

      if n / i as i64 != i as i64 {
         ans += n - n % i as i64;
      }

      ans = (ans + i as i64 * sum_mod(hi, r[i - 1] - 1)) % MOD;

      r.push(hi);
   }

   writeln!(handle, "{ans}").ok();
 }
