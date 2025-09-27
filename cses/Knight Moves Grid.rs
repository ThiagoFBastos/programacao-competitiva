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

   let delta  = [(1, 2), (1, -2), (-1, 2), (-1, -2), (2, 1), (2, -1), (-2, 1), (-2, -1)];

   let mut dist = (0..n).map(|_| vec![-1; n]).collect::<Vec<_>>();

   let mut queue = VecDeque::new();

   dist[0][0] = 0;
   queue.push_back((0, 0));

   while !queue.is_empty() {
      let (x, y) = queue.pop_front().unwrap();

      for &(dx, dy) in delta.iter() {
         let (tx, ty) = (x + dx, y + dy);

         if tx < 0 || tx >= n as i32 || ty < 0 || ty >= n as i32 || dist[tx as usize][ty as usize] != -1 {
            continue;
         }

         dist[tx as usize][ty as usize] = 1 + dist[x as usize][y as usize];
         queue.push_back((tx, ty));
      }
   }

   for i in 0..n {
      for j in 0..n {
         write!(handle, "{} ", dist[i][j]).ok();
      }
      write!(handle, "\n").ok();
   }
 }