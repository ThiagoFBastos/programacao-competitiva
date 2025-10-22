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

   let n = sc.next::<usize>().ok().unwrap();

   let a = (0..n).map(|_| sc.next::<i32>().ok().unwrap()).collect::<Vec<_>>();

   let maxn = *a.iter().max().unwrap() as usize;

   let mut is_prime = vec![true; maxn + 1];

   let mut mobius = vec![-1; maxn + 1];

   let mut frequency = vec![0; maxn + 1];

   for value in a.iter() {
      frequency[*value as usize] += 1;
   }

   let mut answer = n as i64 * (n as i64 - 1) / 2;

   for i in 2..=maxn {

      if is_prime[i] {

         for j in (i..=maxn).step_by(i) {
            is_prime[j] = false;
            mobius[j] *= -1;
         }

         if i as i64 * i as i64 <= maxn as i64 {
            for j in (i * i..=maxn).step_by(i * i) {
               mobius[j] = 0;
            }
         }
      }

      if mobius[i] != 0 {
         let mut total = 0;

         for j in (i..=maxn).step_by(i) {
            total += frequency[j] as i64;
         }

         answer -= total * (total - 1) / 2 * mobius[i];
      }
   }

   writeln!(handle, "{}", answer).ok();
 }
