#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::mem::swap;

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

fn less<T: Ord>(a: T, b: T) -> i32 {
   return if a < b { 1 } else { 0 };
}

fn greater<T: Ord>(a: T, b: T) -> i32 {
   return if a > b { 1 } else { 0 };
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let m = sc.next::<usize>().ok().unwrap();

   let mut pos = vec![0; n + 2];
   let mut arr = vec![0; n + 1];

   for i in 1..=n {
      arr[i] = sc.next::<i32>().ok().unwrap();
      pos[arr[i] as usize] = i;
   }

   let mut answer = 1;

   for i in 2..=n {
      answer += less(pos[i], pos[i - 1]);
   }

   (pos[0], pos[n + 1]) = (n + 1, n + 1);

   for _ in 0..m {

      let mut i = sc.next::<usize>().ok().unwrap();
      let mut j = sc.next::<usize>().ok().unwrap();

      if i != j {

         if (arr[i] - arr[j]).abs() == 1 {

            if arr[i] > arr[j] {
               swap(&mut i, &mut j);
            }

            answer -= less(pos[arr[i] as usize], pos[arr[i] as usize - 1]) + greater(pos[arr[i] as usize], pos[arr[i] as usize + 1]) + greater(pos[arr[j] as usize], pos[arr[j] as usize + 1]);
            (arr[i], arr[j]) = (arr[j], arr[i]);
            (pos[arr[i] as usize], pos[arr[j] as usize]) = (pos[arr[j] as usize], pos[arr[i] as usize]);

            if arr[i] > arr[j] {
               swap(&mut i, &mut j);
            }

            answer += less(pos[arr[i] as usize], pos[arr[i] as usize - 1]) + greater(pos[arr[i] as usize], pos[arr[i] as usize + 1]) + greater(pos[arr[j] as usize], pos[arr[j] as usize + 1]);
         } else {
            answer -= less(pos[arr[i] as usize], pos[arr[i] as usize - 1]) + less(pos[arr[j] as usize], pos[arr[j] as usize - 1]) + less(pos[arr[i] as usize + 1], pos[arr[i] as usize]) + less(pos[arr[j] as usize + 1], pos[arr[j] as usize]);
            (arr[i], arr[j]) = (arr[j], arr[i]);
            (pos[arr[i] as usize], pos[arr[j] as usize]) = (pos[arr[j] as usize], pos[arr[i] as usize]);
            answer += less(pos[arr[i] as usize], pos[arr[i] as usize - 1]) + less(pos[arr[j] as usize], pos[arr[j] as usize - 1]) + less(pos[arr[i] as usize + 1], pos[arr[i] as usize]) + less(pos[arr[j] as usize + 1], pos[arr[j] as usize]);
         }
      }

      writeln!(handle, "{answer}").ok();
   }
 }