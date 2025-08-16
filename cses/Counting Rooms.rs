#![allow(unused_imports)]
use std::collections::VecDeque;
use std::io::Write;
 
struct Scanner {
   buffer : VecDeque<String>
}
 
impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new()
      }
   }
   
   fn next<T : std::str::FromStr>(&mut self) -> T {
 
      if self.buffer.is_empty() {
         let mut input = String::new();
         
         std::io::stdin().read_line(&mut input).ok();
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      front.parse::<T>().ok().unwrap()
   }
}
 
fn dfs(grid: &mut Vec<Vec<char>>, x: usize, y: usize) {
   let n = grid.len();
   let m = grid[0].len();
 
   grid[x][y] = '#';
 
   if x > 0 && grid[x - 1][y] == '.' {
      dfs(grid, x - 1, y);
   }
 
   if y > 0 && grid[x][y - 1] == '.' {
      dfs(grid, x, y - 1);
   }
 
   if x < n - 1 && grid[x + 1][y] == '.' {
      dfs(grid, x + 1, y);
   }
 
   if y < m - 1 && grid[x][y + 1] == '.' {
      dfs(grid, x, y + 1);
   }
}
 
fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
 
   let n = sc.next::<usize>();
   let m = sc.next::<usize>();
 
   let map: Vec<String> = (0..n).map(|_| sc.next::<String>()).collect();
 
   let mut grid: Vec<Vec<char>> = map.iter()
                                 .map(|x| x.chars().collect::<Vec<char>>())
                                 .collect();
 
   let mut rooms = 0;
 
   for x in 0..n {
 
      for y in 0..m {
 
         if grid[x][y] == '.' {
            rooms += 1;
            dfs(&mut grid, x, y);
         }
      }
   }
 
   writeln!(handle, "{rooms}").ok();
}
