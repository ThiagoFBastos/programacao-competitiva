#![allow(unused_imports)]
use std::collections::{VecDeque, HashMap};
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

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
   
   let mut last_pos = HashMap::new();
   let mut subarrays = i64::default();

   let n = sc.next::<usize>().ok().unwrap();

   for i in 1..=n {

      let value = sc.next::<i64>().ok().unwrap();

      let position = *last_pos.get(&value).unwrap_or(&0);

      subarrays += (i - position) as i64 * (n - i + 1) as i64;

      last_pos.insert(value, i);
   }

   writeln!(handle, "{subarrays}").ok();
}