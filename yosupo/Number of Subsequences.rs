#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, HashMap};
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

   const MOD: i64 = 998244353;

   let n = sc.next::<usize>().ok().unwrap();

   let values = (0..n).map(|_| sc.next::<i32>().ok().unwrap()).collect::<Vec<_>>();

   let mut subsequences = HashMap::new();
   let mut count = 0;

   for value in values.iter() {
      let previous = *subsequences.get(value).unwrap_or(&0);

      let total = (1 + count - previous + MOD) % MOD;

      count = (count + total) % MOD;

      subsequences.insert(*value, (previous + total) % MOD);
   }

   writeln!(handle, "{count}").ok();
 }
