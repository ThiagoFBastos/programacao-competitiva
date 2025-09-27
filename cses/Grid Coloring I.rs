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

   let n = sc.next::<usize>().ok().unwrap();
   let m = sc.next::<usize>().ok().unwrap();

   let mut grid = (0..n).map(|_| sc.next::<String>().ok().unwrap())
                                        .map(|s| s.chars().collect::<Vec<_>>())
                                        .collect::<Vec<_>>();
   
   for i in 0..n {
      for j in 0..m {
         if (i + j) % 2 == 0 {
            grid[i][j] = if grid[i][j] == 'A' { 'B' } else { 'A' };
         } else {
            grid[i][j] = if grid[i][j] == 'C' { 'D' } else { 'C' };
         }
      }
   }

   for v in grid.iter() {
      let row = v.iter().collect::<String>();
      writeln!(handle, "{row}").ok();
   }
 }