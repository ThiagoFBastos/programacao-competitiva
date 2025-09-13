#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::Write;
use std::ops::{Add, AddAssign, Sub};
use std::process::Output;

struct Scanner {
   buffer: VecDeque<String>
}
 
impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new()
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> T {
 
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

struct Fenwick<T> {
   data: Vec<Vec<T>>,
   rows: usize,
   columns: usize
}

impl<T: Copy + Default + AddAssign + Sub<Output = T> + Add<Output = T>> Fenwick<T> {

   fn new(rows: usize, columns: usize) -> Self {
      
      let data: Vec<_> = (0..(rows + 1)).map(|_| vec![T::default(); columns + 1]).collect();

      Self {
         data: data,
         rows: rows,
         columns: columns
      }
   }

   fn update(&mut self, mut x: i32, y: i32, value: T) {

      while x as usize <= self.rows {
         let mut _y = y;

         while _y as usize <= self.columns {
            self.data[x as usize][_y as usize] += value;
            _y += _y & -_y;
         }

         x += x & -x;
      }
   }

   fn query(&self, mut x: i32, y: i32) -> T {
      let mut answer = T::default();

      while x > 0 {
         let mut _y = y;

         while _y > 0 {
            answer += self.data[x as usize][_y as usize];
            _y -= _y & -_y;

         }

         x -= x & -x;
      }

      answer
   }

   fn query_subgrid(&self, x0: i32, y0: i32, x1: i32, y1: i32) -> T {
      self.query(x1, y1) - self.query(x1, y0 - 1) - self.query(x0 - 1, y1) + self.query(x0 - 1, y0 - 1)
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>();
   let q = sc.next::<usize>();

   let mut forest = (0..n).map(|_| sc.next::<String>())
                                    .map(|s| s.chars().collect())
                                    .collect::<Vec<Vec<char>>>();

   let mut ft = Fenwick::new(n, n);

   for x in 1..=n {
      for y in 1..=n {

         if forest[x - 1][y - 1] == '*' {
            ft.update(x as i32, y as i32, 1);
         }
      }
   }

   for _ in 0..q {

      let t = sc.next::<u8>();

      if t == 1 {
         let x = sc.next::<usize>();
         let y = sc.next::<usize>();

         let value = if forest[x - 1][y - 1] == '*' 
                        {
                           forest[x - 1][y - 1] = '.'; 
                           -1
                        } 
                        else { 
                           forest[x - 1][y - 1] = '*'; 
                           1 
                        };

         ft.update(x as i32, y as i32, value);
      } else {
         let x0 = sc.next::<i32>();
         let y0 = sc.next::<i32>();
         let x1 = sc.next::<i32>();
         let y1 = sc.next::<i32>();

         writeln!(handle, "{}", ft.query_subgrid(x0, y0, x1, y1)).ok();
      }
   }

}