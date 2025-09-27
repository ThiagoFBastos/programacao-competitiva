#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::hash::Hash;
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

struct Grid {
   mark: [[i32; 9]; 9],
   path: Vec<char>,
   count: i32
}

impl Grid {

   fn new(s: &String) -> Self {
      Self {
         mark: [[0; 9]; 9],
         path: s.chars().collect(),
         count: 0
      }
   }

   fn backtracking(&mut self, k: usize, x: usize, y: usize) {
      if k == 48 {
         self.count += 1;
         return;
      } else if x == 7 && y == 1 {
         return;
      }

      if (self.mark[x - 1][y] + self.mark[x + 1][y] == 0
       && self.mark[x][y - 1] + self.mark[x][y + 1] == 2) 
       || (self.mark[x - 1][y] + self.mark[x + 1][y] == 2 
       && self.mark[x][y - 1] + self.mark[x][y + 1] == 0) {
         return;
      }

      self.mark[x][y] = 0;

      if self.path[k] == '?' {
         if y == 1 {
            if self.mark[x - 1][y] > 0 {
               self.mark[x][y] = 1;
               return;
            }
            
            if self.mark[x + 1][y] > 0 {
               self.backtracking(k + 1, x + 1, y);
            }
         
            if self.mark[x][y + 1] > 0 {
               self.backtracking(k + 1, x, y + 1);
            }
         } else if y == 7 {
            if self.mark[x - 1][y] > 0 {
               self.mark[x][y] = 1;
               return;
            }	
            
            if self.mark[x + 1][y] > 0 {
               self.backtracking(k + 1, x + 1, y);
            }

            if self.mark[x][y - 1] > 0 {
               self.backtracking(k + 1, x, y - 1);
            }
         } else if x == 1 {
         
            if self.mark[x][y - 1] > 0 {
               self.mark[x][y] = 1;
               return;
            }
            
            if self.mark[x + 1][y] > 0 {
               self.backtracking(k + 1, x + 1, y);
            }

            if self.mark[x][y + 1] > 0 {
               self.backtracking(k + 1, x, y + 1);
            }
         } else if x == 7 {
            
            if self.mark[x][y + 1] > 0 {
               self.mark[x][y] = 1;
               return;
            }
            
            if self.mark[x][y - 1] > 0 {
               self.backtracking(k + 1, x, y - 1);
            }

            if self.mark[x - 1][y] > 0 {
               self.backtracking(k + 1, x - 1, y);
            }  
         } else {
            if self.mark[x + 1][y] > 0 {
               self.backtracking(k + 1, x + 1, y);
            }

            if self.mark[x][y - 1] > 0 {
               self.backtracking(k + 1, x, y - 1);
            }

            if self.mark[x][y + 1] > 0 {
               self.backtracking(k + 1, x, y + 1);
            }

            if self.mark[x - 1][y] > 0 {
               self.backtracking(k + 1, x - 1, y);
            }
         }
      } else {
         if self.path[k] == 'L' && self.mark[x][y - 1] > 0 {
            self.backtracking(k + 1, x, y - 1);
         }

         if self.path[k] == 'R' && self.mark[x][y + 1] > 0 {
            self.backtracking(k + 1, x, y + 1);	
         }

         if self.path[k] == 'D' && self.mark[x + 1][y] > 0 {
            self.backtracking(k + 1, x + 1, y);
         }

         if self.path[k] == 'U' && self.mark[x - 1][y] > 0 {
            self.backtracking(k + 1, x - 1, y);
         }	
      }

	   self.mark[x][y] = 1;
   }
}

fn count_paths(grid: &String) -> i32 {
   let mut algorithm = Grid::new(grid);

   for x in 0..=8 {
      algorithm.mark[x].fill(1);
   }

   for x in 0..=8  {
       algorithm.mark[0][x] = 0;
       algorithm.mark[8][x] = 0;
       algorithm.mark[x][0] = 0;
       algorithm.mark[x][8] = 0;
   }

   algorithm.backtracking(0, 1, 1);

   return algorithm.count;
}

#[cfg(test)]
mod unit_tests {
   use super::count_paths;

   #[test]
   fn test_sample_case() {
      let grid = String::from("??????R??????U??????????????????????????LD????D?");
      let expected = 201;

      let result = count_paths(&grid);

      assert_eq!(result, expected);
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let grid = sc.next::<String>().ok().unwrap();

   writeln!(handle, "{}", count_paths(&grid)).ok();
 }