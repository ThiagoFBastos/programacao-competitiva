#![allow(unused_imports)]
use std::cmp::*;
use std::collections::*;

struct Scanner {
   buffer : std::collections::VecDeque<String>,
   eof: bool
}
 
impl Scanner {
 
   fn new() -> Scanner {
      Scanner {
         buffer: std::collections::VecDeque::new(),
         eof: false
      }
   }
 
   fn next<T : std::str::FromStr + Default >(&mut self) -> T {
 
      if self.buffer.len() == 0 {
         let mut input = String::new();
         
         match std::io::stdin().read_line(&mut input) {
            Ok(0) => self.eof = true,
            Ok(_) => {},
            Err(e) => panic!("panico {}", e)
         };

         for word in input.split_whitespace() {
            self.buffer.push_back(word.to_string())
         }
      }

      if self.eof {
         return T::default();
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      front.parse::<T>().ok().unwrap()
   }

   fn read_line(&mut self) -> String {
      let mut input = String::new();
         
      match std::io::stdin().read_line(&mut input) {
         Ok(0) => self.eof = true,
         Ok(_) => {},
         Err(e) => panic!("{}", e)
      };

      return input;
   }

   fn is_eof(&mut self) -> bool {
      return self.eof;
   }
}

fn main() {
  
   let mut sc = Scanner::new();

   let days = sc.next::<usize>();

   let mut sum_prices = f64::default();
   let mut items = usize::default();

   for i in 1..=days {

      let price = sc.next::<f64>();

      let line = sc.read_line();

      let fruits: Vec<&str> = line.trim()
                                 .split_whitespace()
                                 .collect();  

      println!("day {}: {} kg", i, fruits.len());

      sum_prices += price;
      items += fruits.len();
   }

   let avg_price = sum_prices / (days as f64);
   let avg_items = (items as f64) / (days as f64);

   println!("{:.2} kg by day", avg_items);
   println!("R$ {:.2} by day", avg_price);
}