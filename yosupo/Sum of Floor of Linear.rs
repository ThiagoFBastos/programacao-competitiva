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

fn linsum(a: i128, b: i128) -> i128 {
   return (a + b) * (b - a + 1) / 2;
}

fn sum(n: i128, m: i128, a: i128, b: i128) -> i128 {
   if a == 0 {
      return b * n;
   }

	let k = (a * (n - 1) + b) / m;
	let s = b * n + a * linsum(0, n - 1);
	let t = k * (n - 1) - ((a+(-b-1)%a)%a+m * linsum(1, k) - k * (b + 1) - sum(k + 1, a, m % a, (a+(-b-1)%a)%a)) / a;

	return s - m * t;
}

fn query(n: i128, m: i128, a: i128, b: i128) -> i128 {
   let s = b * n + a * linsum(0, n - 1) - sum(n, m, a, b);
   return s / m;
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let t = sc.next::<usize>().ok().unwrap();

   for _ in 0..t {

      let n = sc.next::<i128>().ok().unwrap();
      let m = sc.next::<i128>().ok().unwrap();
      let a = sc.next::<i128>().ok().unwrap();
      let b = sc.next::<i128>().ok().unwrap();

      writeln!(handle, "{}", query(n, m, a, b)).ok();
   }
 }
