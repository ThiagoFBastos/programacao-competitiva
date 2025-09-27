#![allow(unused_imports)]
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

fn digit_query(k: i64) -> i64 {
   let mut p = 1_i64;
   let mut cnt = 0_i64;
   let mut i = 1_i64;

   while cnt < k {
      cnt += 9 * p * i;
      i += 1;
      p *= 10;
   }

   p /= 10;
   i -= 1;
   cnt -= 9 * p * i;

   let mut x = p - 1 + (k - cnt + i - 1) / i;

   cnt += i * ((k - cnt + i - 1) / i - 1);

   for _ in 0..i - k + cnt {
      x /= 10;
   }

   x % 10
}

#[cfg(test)]
mod tests {
   use super::*;

   #[test]
   fn test_seventh_digit() {
      const POS: i64 = 7;
      const EXPECTED: i64 = 7;

      let result = digit_query(POS);

      assert_eq!(result, EXPECTED);
   }

   #[test]
   fn test_nineteenth_digit() {
      const POS: i64 = 19;
      const EXPECTED: i64 = 4;
      
      let result = digit_query(POS);

      assert_eq!(result, EXPECTED);
   }

   #[test]
   fn test_twelveth_digit() {
      const POS: i64 = 12;
      const EXPECTED: i64 = 1;
      
      let result = digit_query(POS);

      assert_eq!(result, EXPECTED);
   }

   #[test]
   fn test_first_digit() {
      const POS: i64 = 1;
      const EXPECTED: i64 = 1;
      
      let result = digit_query(POS);

      assert_eq!(result, EXPECTED);
   }

   #[test]
   fn test_tenth_digit() {
      const POS: i64 = 10;
      const EXPECTED: i64 = 1;
      
      let result = digit_query(POS);

      assert_eq!(result, EXPECTED);
   }

   #[test]
   fn test_eleventh_digit() {
      const POS: i64 = 11;
      const EXPECTED: i64 = 0;
      
      let result = digit_query(POS);

      assert_eq!(result, EXPECTED);
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let queries = sc.next::<usize>().ok().unwrap();

   for _ in 0..queries {
      let n = sc.next::<i64>().ok().unwrap();

      writeln!(handle, "{}", digit_query(n)).ok();
   }
 }