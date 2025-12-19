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

#[derive(Clone)]
struct MatrixMod2 {
   matrix: Vec<Vec<i32>>,
   rows: usize,
   cols: usize
}

impl MatrixMod2 {

   fn new(rows: usize, cols: usize) -> Self {

      Self {
         matrix: vec![vec![0; cols]; rows],
         rows,
         cols
      }
   }

   fn identity(rows: usize, cols: usize) -> Self {
      let mut res = MatrixMod2::new(rows, cols);

      for i in 0..rows {
         for j in 0..cols {
            res.matrix[i][j] = if i == j { 1 } else { 0 };
         }
      }

      res
   }

   fn multiply(&self, other: &MatrixMod2) -> MatrixMod2 {

      assert!(self.cols == other.rows);

      let mut res = MatrixMod2::new(self.rows, other.cols);

      for i in 0..self.rows {
         for j in 0..other.cols {
            for k in 0..self.cols {
               res.matrix[i][j] = (res.matrix[i][j] + self.matrix[i][k] * other.matrix[k][j]) % 2;
            }
         }
      }
      return res;
   }

   fn pow(&self, mut n: u32) -> MatrixMod2 {
      assert!(self.rows == self.cols);

      let mut res = Self::identity(self.rows, self.cols);
      let mut matrix = self.clone();

      while n > 0 {

         if n & 1 == 1 {
            res = res.multiply(&matrix);
         }

         matrix = matrix.multiply(&matrix);
         n >>= 1;
      }

      res
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   //a[i][j] = if grid[i][j] == '#' -> 0 else (\sum vizinhos + a[i][j]) % 2

   let n = sc.next::<usize>().unwrap();
   let k = sc.next::<u32>().unwrap();

   let mut grid = Vec::with_capacity(n);

   for _ in 0..n {
      let row = sc.next::<String>().unwrap().chars().collect::<Vec<_>>();
      grid.push(row);
   }

   let mut rec_matrix = MatrixMod2::new(n*n, n*n);

   for i in 0..n {
      for j in 0..n {

         if grid[i][j] == '#' {
            continue;
         }

         let cur_pos = i * n + j;

         for dx in -1..=1 {
            for dy in -1..=1 {
               let x = i as i32 + dx;
               let y = j as i32 + dy;

               if x < 0 || x >= n as i32 || y < 0 || y >= n as i32 {
                  continue;
               }

               let other_pos = x as usize * n + y as usize;

               rec_matrix.matrix[cur_pos][other_pos] = 1;
            }
         }
      }
   }

   let result_rec_matrix = rec_matrix.pow(k);
   let mut result_grid = grid.clone();

   for i in 0..n {
      for j in 0..n {
         if grid[i][j] == '#' {
            continue;
         }

         let mut sum = 0;
        

         for k in 0..n*n {
            let x = k / n;
            let y = k % n;
            let chr = if grid[x][y] == '#' { '0' } else { grid[x][y] };
            let initial = chr.to_digit(10).unwrap() as i32;

            sum += result_rec_matrix.matrix[i * n + j][k] * initial % 2;
         }

         sum %= 2;

         result_grid[i][j] = (sum % 2 + 48) as u8 as char;
      }
   }

   for row in result_grid.iter() {
      let str = row.iter().collect::<String>();
      writeln!(handle, "{}", str).ok();
   }
 }
