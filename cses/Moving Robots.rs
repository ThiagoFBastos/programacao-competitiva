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

macro_rules! double {
    ($x: expr) => {
      if ($x) { 1.0 } else { 0.0 }  
    };
}

fn moving(x: usize, y: usize, k: usize) -> [[f64; 8]; 8] {
   let mut g = [[0.0; 8]; 8];
   let mut p = [[0.0; 8]; 8];

   p[x][y] = 1.0;

   for _  in 0..k {
      for x in 0..8 {
         for y in 0..8 {
            let s = p[x][y] / (double!(x > 0) + double!(y > 0) + double!(x < 7) + double!(y < 7));

            if x > 0 {
               g[x - 1][y] += s;
            }

            if y > 0 {
               g[x][y - 1] += s;
            }

    				if x < 7 {
              g[x + 1][y] += s;
            }

				    if y < 7 {
              g[x][y + 1] += s;
            }
         }
      }

      p = g.clone();
      g = [[0.0; 8]; 8];
   }

   return p;
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let k = sc.next::<usize>().ok().unwrap();

   let mut ans = [[1.0; 8]; 8];
   let mut answer = 0.0;

   for i in 0..8 {
      for j in 0..8 {
         let p = moving(i, j, k);

         for x in 0..8 {
            for y in 0..8 {
               ans[x][y] *= 1.0 - p[x][y];
            }
         }
      }
   }

   for x in 0..8 {
      for y in 0..8 {
         answer += ans[x][y];
      }
   }

   writeln!(handle, "{:.6}", answer).ok();
 }
