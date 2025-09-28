#![allow(unused_imports)]
use std::collections::{VecDeque, BTreeMap};
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

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const MOD: i64 = 1_000_000_007;

   let n = sc.next::<usize>().ok().unwrap();

   let mut frequency = BTreeMap::new();
   let mut answer = 1_i64;

   for _ in 0..n {
      let value = sc.next::<i32>().ok().unwrap();
      frequency.insert(value, *frequency.get(&value).unwrap_or(&0_i64) + 1);
   }

   for (_, count) in frequency.iter() {
      answer = answer * (1 + *count) % MOD;
   }

   answer = (answer + MOD - 1) % MOD;

   writeln!(handle, "{answer}").ok();
 }