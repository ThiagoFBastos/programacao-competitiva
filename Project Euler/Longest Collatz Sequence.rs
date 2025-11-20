#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, HashMap};
use std::io::{self, Error, ErrorKind, Write};
use std::ops::Add;

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
         self.buffer.push_back("".to_string());
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn collatz(n: u64) -> u64 {
   return if n % 2 == 0 { n / 2} else { 3 * n + 1};
}

fn find_chains(n: u64, chain: &mut HashMap<u64, u32>) -> u32 {
   if chain.contains_key(&n) {
      return *chain.get(&n).unwrap();
   }

   let count = find_chains(collatz(n), chain);

   chain.insert(n, count + 1);

   return count + 1;
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   const N: u64 = 1_000_000;

   let mut chain = HashMap::new();

   chain.insert(1, 1);

   for i in 2..N {
      _ = find_chains(i, &mut chain);
   }

   let max_chain = chain.iter().filter(|pair| *pair.0 <= N).map(|pair| (pair.1, pair.0)).max();

   let target = max_chain.unwrap().1;

   writeln!(handle, "{}", target).ok();
}
