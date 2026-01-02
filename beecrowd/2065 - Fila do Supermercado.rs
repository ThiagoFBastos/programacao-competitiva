#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::Reverse;
use std::collections::{BinaryHeap, VecDeque};
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

   let n = sc.next::<usize>().unwrap();
   let m = sc.next::<usize>().unwrap();

   let cs = (0..n).map(|_| sc.next::<i32>().unwrap()).collect::<Vec<_>>();
   let vs = (0..m).map(|_| sc.next::<i32>().unwrap()).collect::<Vec<_>>();

   let mut pq = BinaryHeap::new();

   for i in 0..n {
      pq.push(Reverse((0, i)));
   }

   for &v in vs.iter() {
      let (mut time, index) = pq.pop().unwrap().0;

      time += cs[index] * v;
      pq.push(Reverse((time, index)));
   }

   let mut total_time = 0;

   while !pq.is_empty() {
      let (time, _) = pq.pop().unwrap().0;
      total_time = total_time.max(time);
   }

   writeln!(writer, "{}", total_time).ok();
}
