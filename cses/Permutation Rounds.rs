#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::hash::Hash;
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

fn cycles(p: &[usize]) -> Vec<usize> {
   let n = p.len();
   let mut vis = vec![false; n];
   let mut sizes = Vec::new();

   for v in 0..n {
      if vis[v] {
         continue;
      }

      let mut i = 0;
      let mut vertex = v;

      loop {
          i += 1;
          vis[vertex] = true;
          vertex = p[vertex];

          if vis[vertex] {
            break;
          }
      }

      sizes.push(i);
   }

   sizes
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const MOD: i64 = 1_000_000_007;

   let n = sc.next::<usize>().ok().unwrap();

   let p = (0..n).map(|_| sc.next::<usize>().ok().unwrap() - 1).collect::<Vec<_>>();

   let sizes = cycles(&p);

   let lcm = {

      let mut answer = 1;
      let maxn = *sizes.iter().max().unwrap();
      let mut has_value = vec![false; maxn + 1];

      sizes.iter().for_each(|val| {
         has_value[*val] = true;
      });

      let mut is_prime = vec![true; maxn + 1];

      for p in 2..=maxn {

         if !is_prime[p] {
            continue;
         }

         let mut max_power = 0;

         for i in (p..=maxn).step_by(p) {
            is_prime[i] = false;

            if !has_value[i] {
               continue;
            }

            let mut k = i;
            let mut power = 0;

            while k % p == 0 {
               power += 1;
               k /= p;
            }

            max_power = max_power.max(power);
         }

         for _  in 0..max_power {
            answer = answer * p as i64 % MOD;
         }
      }

      answer
   };

   writeln!(handle, "{}", lcm).ok();
 }
