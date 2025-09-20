#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::Write;

use crate::nt::PrimeNumber;

struct Scanner {
   buffer: VecDeque<String>
}
 
impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new()
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> T {
 
      if self.buffer.is_empty() {
         let mut input = String::new();
         
         std::io::stdin().read_line(&mut input).ok();
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      front.parse::<T>().ok().unwrap()
   }
}

mod nt {
   pub struct PrimeNumber {
      is_prime: Vec<bool>,
      prime_numbers: Vec<u32>,
      maxn: usize
   }

   impl PrimeNumber {

      pub fn new() -> Self {

         const MAXN: usize = 1414214;

         let mut p = Self {
            is_prime: vec![true; MAXN],
            prime_numbers: Vec::new(),
            maxn: MAXN
         };

         p.compute_primes();

         return p;
      }

      fn compute_primes(&mut self) {
         let mut p: usize = 2;

         self.is_prime[1] = false;

         while p * p < self.maxn {

            if self.is_prime[p] {
   
               for i in (2*p..self.maxn).step_by(p) {
                  self.is_prime[i] = false;
               }
            }

            p += 1;
         }

         for p in 2..self.maxn {
            if self.is_prime[p] {
               self.prime_numbers.push(p as u32);
            }
         }
      }

      fn is_prime(&self, n: u64) -> bool {
         if n < self.maxn as u64 {
            return self.is_prime[n as usize];
         }

         for &p in self.prime_numbers.iter() {
            if p as u64 * p as u64 > n {
               break;
            } else if n % p as u64 == 0 {
               return false;
            }
         }

         true
      }

      pub fn next_prime(&self, mut n: u64) -> u64 {
         loop {
            n += 1;
            
            if self.is_prime(n) {
               return n;
            }
         }
      }
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let tests = sc.next::<usize>();

   let search = PrimeNumber::new();

   for _ in 0..tests {

      let n = sc.next::<u64>();

      writeln!(handle, "{}", search.next_prime(n)).ok();
   }
}