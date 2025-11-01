#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::ops::{Mul, Sub};
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

#[derive(Copy, Clone, Default)]
struct Vector<T> {
   dx: T,
   dy: T
}

impl<T> Vector<T> {

   fn new(dx: T, dy: T) -> Self {

      Self {
         dx: dx,
         dy: dy
      }
   }
}

impl<T: Sub<Output = T>> Sub for Vector<T> {

   type Output = Self;

   fn sub(self, other: Vector<T>) -> Self::Output {

      Self {
         dx: self.dx - other.dx,
         dy: self.dy - other.dy
      }
   }
}

impl<T: Mul<Output = T> + Sub<Output = T>> Mul for Vector<T> {

   type Output = T;

   fn mul(self, other: Self) -> Self::Output {
       self.dx * other.dy - self.dy * other.dx
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let tests = sc.next::<usize>().ok().unwrap();

   for _ in 0..tests {

      let ax = sc.next::<i64>().ok().unwrap();
      let ay = sc.next::<i64>().ok().unwrap();
      
      let bx = sc.next::<i64>().ok().unwrap();
      let by = sc.next::<i64>().ok().unwrap();
      
      let cx = sc.next::<i64>().ok().unwrap();
      let cy = sc.next::<i64>().ok().unwrap();

      let pa = Vector::new(ax, ay);
      let pb = Vector::new(bx, by);
      let pc = Vector::new(cx, cy);

      let pba = pb - pa;
      let pca = pc - pa;

      let cross = pca * pba;

      if cross > 0 {
         writeln!(handle, "RIGHT").ok();
      } else if cross < 0 {
          writeln!(handle, "LEFT").ok();
      } else {
         writeln!(handle, "TOUCH").ok();
      }
   }
 }
