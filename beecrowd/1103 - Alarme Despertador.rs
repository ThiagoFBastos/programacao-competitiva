#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};

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
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   loop {
      let h1 = sc.next::<i32>().unwrap();
      let m1 = sc.next::<i32>().unwrap();
      let h2 = sc.next::<i32>().unwrap();
      let m2 = sc.next::<i32>().unwrap();

      if (h1, m1, h2, m2) == (0, 0, 0, 0) {
         break;
      }

      let t1 = 60 * h1 + m1;
      let t2 = 60 * h2 + m2;

      let minutes = if t1 < t2 {
         t2 - t1
      } else {
         24 * 60 - t1 + t2
      };

      writeln!(writer, "{}", minutes).ok();
   }
}