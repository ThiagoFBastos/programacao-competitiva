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
         self.buffer.push_back("".to_string());
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn max_four_adjacent_product(grid: &Vec<Vec<i32>>, dx: i32, dy: i32) -> i32 {

   let n = grid.len();
   let m = grid[0].len();
   let mut max_product = 0;

   for i in 0..n {
      for j in 0..m {
         let mut is_valid = true;
         let mut product = 1;

         for k in 0..4 {
            let x = i as i32 + k * dx;
            let y = j as i32 + k * dy;

            if x < 0 || x >= n as i32 || y < 0 || y >= m as i32 {
               is_valid = false;
               break;
            }

            product *= grid[x as usize][y as usize];
         }

         if is_valid {
            max_product = max_product.max(product);
         }
      }
   }

   max_product
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const N: usize = 20;

   let mut grid = vec![vec![0; N]; N];

   for i in 0..N {
      for j in 0..N {
         grid[i][j] = sc.next::<i32>().ok().unwrap();
      }
   }

   let up = max_four_adjacent_product(&grid, -1, 0);
   let left = max_four_adjacent_product(&grid, 0, -1);
   let diagonal = max_four_adjacent_product(&grid, 1, 1);
   let antidiagonal = max_four_adjacent_product(&grid, 1, -1);

   let answer = up.max(left.max(diagonal.max(antidiagonal)));

   writeln!(handle, "{}", answer).ok();
}
