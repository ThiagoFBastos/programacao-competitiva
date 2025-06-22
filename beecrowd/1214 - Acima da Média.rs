#![allow(unused_imports)]
use std::cmp::*;
use std::collections::*;

struct Scanner {
   buffer : std::collections::VecDeque<String>
}
 
impl Scanner {
 
   fn new() -> Scanner {
      Scanner {
         buffer: std::collections::VecDeque::new()
      }
   }
 
   fn next<T : std::str::FromStr >(&mut self) -> T {
 
      if self.buffer.len() == 0 {
         let mut input = String::new();
         std::io::stdin().read_line(&mut input).ok();
         for word in input.split_whitespace() {
            self.buffer.push_back(word.to_string())
         }
      }
 
      let front = self.buffer.pop_front().unwrap();
      front.parse::<T>().ok().unwrap()
   }
}

fn average(arr: &Vec<i32>) -> f64 {
   let mut sum = f64::default();
   let n = arr.len() as f64;

   for val in arr {
      sum += *val as f64;
   }

   return sum / n;
}

fn main() {
  
   let mut scanner = Scanner::new();

   let tests = scanner.next::<usize>();

   for _i in 0..tests {
      
      let n = scanner.next::<usize>();

      let mut grades: Vec<i32> = vec![0; n];

      for j in 0..n {
         grades[j] = scanner.next::<i32>();
      }

      let avg = average(&grades);
      let mut above = i32::default();
      
      for val in grades.into_iter() {
         if val as f64 > avg {
            above += 1;
         }
      }

      let percentile = (above as f64) / (n as f64) * 100.0;

      println!("{:.3}%", percentile);
   }
}