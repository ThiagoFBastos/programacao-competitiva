#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, BTreeSet};
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
         self.buffer.push_back("".to_string());
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn divisors(n: i32) -> Vec<i32> {
   let mut div = Vec::new();
   let mut i = 1;

   while i * i <= n {

      if n % i == 0 {
         div.push(i);

         if i * i != n {
            div.push(n / i);
         }
      }

      i += 1;
   }

   return div;
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();

   let seals = (0..n).map(|_| sc.next::<i32>().unwrap()).collect::<BTreeSet<_>>();

   let nums = seals.into_iter().collect::<Vec<_>>();

   const MAX: i32 = 1_000_000_000;

   if nums.len() == 1 {
      writeln!(handle, "1 {}", MAX - 1).ok();
      return;
   }

   let m = nums.len().min(3);
   let mut fixed = BTreeSet::new();
   let mut rounds = 2;

   for i in 0..m {
      for j in i+1..m {
         let divs = divisors((nums[i] - nums[j]).abs());

         for &d in divs.iter() {

            if d == 1 {
               continue;
            }

            let mut mods = BTreeSet::new();

            for &val in nums.iter() {
               mods.insert(val % d);

               if mods.len() > 2 {
                  break;
               }
            }

            if mods.len() <= 2 {
               rounds = rounds.min(mods.len());
               fixed.insert((d, mods.len()));
            }
         }
      }
   }

   if nums.len() == 2 && rounds == 2 {
      writeln!(handle, "2 {}", MAX - 1).ok();
      return;
   }

   let count = fixed.iter().filter(|tup| tup.1 == rounds).count();

   writeln!(handle, "{} {}", rounds, count).ok();
 }
