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

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const N: usize = 2_05;

   let mut grid = [[0; N]; N];

   let n = sc.next::<usize>().ok().unwrap();

   for i in 0..n {
      for j in 0..n {
         let mut mex = [false; N];

         for k in 0..i {
            mex[grid[k][j]] = true;
         }

         for k in 0..j {
            mex[grid[i][k]] = true;
         }

         let val = &mut grid[i][j];

         while mex[*val] {
            *val += 1;
         }

         write!(handle, "{} ", val).ok();
      }

      write!(handle, "\n").ok();
   }
 }