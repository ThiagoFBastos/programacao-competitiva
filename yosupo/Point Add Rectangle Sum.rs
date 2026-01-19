/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-18
 */

#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};
use std::ops::AddAssign;

use crate::Query::*;

struct Scanner {
   buffer: VecDeque<String>,
   reader: io::BufReader<io::Stdin>
}

impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new(),
         reader: io::BufReader::new(io::stdin())
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
 
      if self.buffer.is_empty() {
         let mut input = String::new();

         match self.reader.read_line(&mut input) {
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

         if self.buffer.is_empty() {
            self.buffer.push_back("".to_string());
         }
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }

   fn read_line(&mut self) -> io::Result<String> {
      let mut input = String::new();

      match self.reader.read_line(&mut input) {
         Ok(0) => {
            return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
         } Ok(_) => {
            
         } Err(e) => {
            return Err(e);
         }
      }

      Ok(input)
   }
}

trait Constants {
   fn initial() -> Self;
}

struct BIT2D<T> {
   sum: Vec<Vec<T>>,
   x: Vec<i32>,
   y: Vec<Vec<i32>>
}

impl<T: Copy + Constants + AddAssign> BIT2D<T> {

   fn new(mut points: Vec<(i32, i32)>) -> Self {
      let mut x = points.iter().map(|p| p.0).collect::<Vec<_>>();

      x.sort();
      x.dedup();

      points.sort_by_key(|p| p.1);

      let mut y = vec![vec![]; x.len() + 1];
      let mut sum = vec![vec![]; x.len() + 1];

      for &(i, j) in points.iter() {
         let mut k = Self::find_pos(&x, i);

         while k < y.len() {

            if y[k].is_empty() || *y[k].last().unwrap() != j {
               y[k].push(j);
            }

            k += (k as i32 & -(k as i32)) as usize;
         }
      }

      for i in 0..y.len() {
         sum[i] = vec![T::initial(); y[i].len() + 1];
      }

      Self {
         sum: sum,
         x: x,
         y: y
      }
   }

   fn find_pos(coords: &Vec<i32>, v: i32) -> usize {
      coords.binary_search_by(|element| match element.cmp(&v) {
         std::cmp::Ordering::Equal => std::cmp::Ordering::Less,
         ord => ord
      }).unwrap_err()
   }

   fn update(&mut self, i: i32, j: i32, value: T) {

      let mut x = Self::find_pos(&self.x, i);

      while x < self.sum.len() {

         let mut y = Self::find_pos(&self.y[x], j);

         while y < self.sum[x].len() {
            self.sum[x][y] += value;
            y += (y as i32 & -(y as i32)) as usize;
         }

         x += (x as i32 & -(x as i32)) as usize;
      }
   }

   fn query(&self, i: i32, j: i32) -> T {
      let mut x = Self::find_pos(&self.x, i);
      let mut result = T::initial();

      while x > 0 {

         let mut y = Self::find_pos(&self.y[x], j);

         while y > 0 {
            result += self.sum[x][y];
            y -= (y as i32 & -(y as i32)) as usize;
         }

         x -= (x as i32 & -(x as i32)) as usize;
      }

      result
   }
}

impl Constants for i64 {
   fn initial() -> Self {
       return 0;
   }
}

enum Query {
   Update(i32, i32, i64),
   Query(i32, i32, i32, i32)
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();
   
   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let mut points = Vec::with_capacity(n);
   let mut keys = Vec::with_capacity(n + q);
   let mut queries = Vec::with_capacity(q);

   for _ in 0..n {
      let x = sc.next::<i32>().unwrap();
      let y = sc.next::<i32>().unwrap();
      let w = sc.next::<i64>().unwrap();

      points.push((x, y, w));
      keys.push((x, y));
   }

   for _ in 0..q {
      let t = sc.next::<u8>().unwrap();

      if t == 0 {
         let x = sc.next::<i32>().unwrap();
         let y = sc.next::<i32>().unwrap();
         let w = sc.next::<i64>().unwrap();

         queries.push(Update(x, y, w));

         keys.push((x, y));
      } else {

         let l = sc.next::<i32>().unwrap();
         let d = sc.next::<i32>().unwrap();
         let r = sc.next::<i32>().unwrap() - 1;
         let u = sc.next::<i32>().unwrap() - 1;

         queries.push(Query(l, d, r, u));

         keys.push((l - 1, d - 1));
         keys.push((r, u));
         keys.push((r, d - 1));
         keys.push((l - 1, u));
      }
   }

   let mut bit2d = BIT2D::new(keys);

   for (x, y, w) in points {
      bit2d.update(x, y, w);
   }

   for query in queries {
      match query {
         Update(x, y, w) => {
            bit2d.update(x, y, w);
         },
         Query(x0, y0, x1, y1) => {
            let sum = bit2d.query(x1, y1) - bit2d.query(x1, y0 - 1) - bit2d.query(x0 - 1, y1) + bit2d.query(x0 - 1, y0 - 1);

            writeln!(writer, "{}", sum).ok();
         }
      }
   }
}
