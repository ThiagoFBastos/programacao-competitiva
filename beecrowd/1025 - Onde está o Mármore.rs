#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::*;
use std::collections::*;

struct Scanner {
   buffer : VecDeque<String>,
   eof: bool
}
 
impl Scanner {
 
   fn new() -> Scanner {
      Scanner {
         buffer: VecDeque::new(),
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

   fn is_eof(&self) -> bool {
      self.eof
   }
}

fn binary_search(arr: &Vec<i32>, target: i32) -> i32 {
   let mut lo: usize = 0;
   let mut hi: usize = arr.len() - 1;

   while lo < hi {
      let mid = (lo + hi) / 2;

      if arr[mid] >= target {
         hi = mid;
      } else {
         lo = mid + 1;
      }
   }

   return if arr[hi] == target { (hi + 1) as i32 } else { -1 }; 
}

fn main() {

   let mut sc = Scanner::new();
   let mut case = 1;

   loop {

      let n = sc.next::<usize>();
      let q = sc.next::<usize>();

      if n == 0 && q == 0 {
         break;
      }

      let mut arr = vec![0; n];

      for i in 0..n {
         arr[i] = sc.next::<i32>();
      }

      arr.sort();

      println!("CASE# {}:", case);

      for _i in 0..q {
         let target = sc.next::<i32>();

         let pos = binary_search(&arr, target);

         if pos == -1 {
            println!("{} not found", target);
         } else {
            println!("{} found at {}", target, pos);
         }
      }


      case += 1;
   }
}