#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, BTreeMap};
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

   let tests = sc.next::<usize>().unwrap();

   let mut frequency = BTreeMap::new();

   for _ in 0..tests {
      let n = sc.next::<i32>().unwrap();
      frequency.insert(n, *frequency.get(&n).unwrap_or(&0) + 1);
   }

   for (key, count) in frequency.iter() {
      writeln!(writer, "{} aparece {} vez(es)", key, count).ok();
   }
}