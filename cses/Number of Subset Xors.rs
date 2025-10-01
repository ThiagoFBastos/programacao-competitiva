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
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn msb(x: i32) -> Result<u32, &'static str> {
   if x == 0 {
      return Err("argument is zero");
   }

   let log = 31 - x.leading_zeros();

   Ok(log)
}

fn maximum_xor(x: &[i32]) -> i32 {
   const N: usize = 30;

   let mut gauss = (0..N).map(|_| Vec::new()).collect::<Vec<_>>();
   let mut k = 0;

   x.iter().for_each(|value| {
      if *value > 0 {
         gauss[msb(*value).ok().unwrap() as usize].push(*value);
      }
   });

   for i in (0..N).rev() {
      if gauss[i].is_empty() {
         continue;
      }

      k += 1;

      let pivot = gauss[i][0];

      for value in gauss[i].clone().iter() {
         let xor = *value ^ pivot;

         if xor > 0 {
            gauss[msb(xor).ok().unwrap() as usize].push(xor);
         }
      }
   }

   1 << k
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();

   let x = (0..n).map(|_| sc.next::<i32>().ok().unwrap()).collect::<Vec<_>>();

   let result = maximum_xor(&x);

   writeln!(handle, "{}", result).ok();
 }