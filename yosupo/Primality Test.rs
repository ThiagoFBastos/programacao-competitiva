/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-02-07
 */

#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};

struct Scanner {
   buffer: VecDeque<String>,
   reader: io::BufReader<io::Stdin>
}

impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new(),
         reader: io::BufReader::new(io::stdin())
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
 
      if self.buffer.is_empty() {
         let mut input = String::new();

         match self.reader.read_line(&mut input) {
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

         if self.buffer.is_empty() {
            self.buffer.push_back("".to_string());
         }
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }

   fn read_line(&mut self) -> io::Result<String> {
      let mut input = String::new();

      match self.reader.read_line(&mut input) {
         Ok(0) => {
            return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
         } Ok(_) => {
            
         } Err(e) => {
            return Err(e);
         }
      }

      Ok(input)
   }
}

fn bin_exp(n: i128, p: i128, m: i128) -> i128 {
   if p == 0 {
      return 1;
   }

   let mut res = bin_exp(n, p >> 1, m);

   res = res * res % m;

   if p & 1 == 1 {
      res = res * n % m;
   }

   return res;
}

fn miller(n: i64) -> bool {
   let primes: [i64; 9] = [2, 3, 5, 7, 11, 13, 17, 19, 23];

   for &p in primes.iter() {
      if n % p == 0 {
         return n == p;
      }
   }

   if n < *primes.last().unwrap() {
      return false;
   }

   let mut t = n - 1;
   let mut s = 0;

   while t & 1 == 0 {
      t >>= 1;
      s += 1;
   }

   for &p in primes.iter() {
      let mut pow = bin_exp(p as i128, t as i128, n as i128);

      if pow == 1 {
         continue;
      }      

      let mut ok = false;

      for _ in 0..s {
         if pow == n as i128 - 1 {
            ok = true;
            break;
         }

         pow = pow * pow % n as i128;
      }

      if !ok {
         return false;
      }
   }

   return true;
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let q = sc.next::<usize>().unwrap();

   for _ in 0..q {
      let n = sc.next::<i64>().unwrap();
      writeln!(writer, "{}", if miller(n) { "Yes" } else { "No" }).ok();
   }
}
