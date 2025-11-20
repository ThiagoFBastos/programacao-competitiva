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
         self.buffer.push_back("".to_string());
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn count_triangular_number_divisors(n: i32) -> i32 {
   let mut factors = HashMap::new();

   let factorize = |mut n, factors: &mut HashMap<i32, i32>| {
      let mut i = 2;

      while i * i <= n {
         if n % i == 0 {
            let mut count = 0;

            while n % i == 0 {
               n /= i;
               count += 1;
            }

            factors.insert(i, *factors.get(&i).unwrap_or(&0) + count);
         }

         i += 1;
      }

      if n > 1 {
         factors.insert(n, 1);
      }
   };

   let (mut a, mut b) = (n, n + 1);

   if a % 2 == 0 {
      a /= 2;
   } else {
      b /= 2;
   }

   factorize(a, &mut factors);
   factorize(b, &mut factors);

   let mut count = 1;

   for (_, k) in factors.iter() {
      count *= *k + 1;
   }

   return count;
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let count = sc.next::<i32>().ok().unwrap();

   let mut i = 1;

   let answer = loop {

      if count_triangular_number_divisors(i) > count {
         break i * (i + 1) / 2;
      }

      i += 1;
   };

   writeln!(handle, "{}", answer).ok();
}
