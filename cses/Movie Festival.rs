#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::cmp::Ordering;

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

   let n = sc.next::<usize>().ok().unwrap();

   let mut time = (0..n).map(|_| {
      let x = sc.next::<i32>().ok().unwrap();
      let y = sc.next::<i32>().ok().unwrap();

      (x, y)
   }).collect::<Vec<_>>();

   time.sort_by_key(|t| t.1);

   let mut max_movies = vec![0; n];

   max_movies[0] = 1;

   for i in 1..n {

      let pos = time.binary_search_by(|elem| match elem.1.cmp(&time[i].0) {
         Ordering::Equal => Ordering::Less,
         ord => ord
      }).unwrap_err();

      if pos >= 1 {
         max_movies[i] = 1 + max_movies[pos - 1];
      } else {
         max_movies[i] = 1;
      }

      max_movies[i] = max_movies[i].max(max_movies[i - 1]);
   }

   writeln!(handle, "{}", max_movies.last().unwrap()).ok();
 }