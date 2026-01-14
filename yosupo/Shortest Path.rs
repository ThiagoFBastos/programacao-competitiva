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

   fn read_line(&mut self) -> io::Result<String> {
       let mut input = String::new();

      match self.reader.read_line(&mut input) {
         Ok(0) => {
            return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
         } Ok(_) => {
            
         } Err(e) => {
            return Err(e);
         }
      }

      Ok(input)
   }
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let m = sc.next::<usize>().unwrap();
   let s = sc.next::<usize>().unwrap();
   let t = sc.next::<usize>().unwrap();

   let mut adj = vec![vec![]; n];
   
   for _ in 0..m {
      let u = sc.next::<usize>().unwrap();
      let v = sc.next::<usize>().unwrap();
      let w = sc.next::<i32>().unwrap();

      adj[u].push((v, w));
   }

   let mut dist = vec![None; n];
   let mut parent = vec![None; n];

   let mut pq = BinaryHeap::new();

   pq.push(Reverse((0, s, None)));

   while !pq.is_empty() {
      let (cost, u, p) = pq.pop().unwrap().0;

      if dist[u].is_some() {
         continue;
      }

      dist[u] = Some(cost);
      parent[u] = p;

      if u == t {
         break;
      }

      for &(v, w) in adj[u].iter() {
         if parent[v].is_some() {
            continue;
         }

         pq.push(Reverse((cost + w as i64, v, Some(u))));
      }
   }

   if dist[t].is_none() {
      writeln!(writer, "-1").ok();
      return;
   }

   let mut path = Vec::new();
   let mut vertex = t;

   loop {
      path.push(vertex);

      if parent[vertex].is_none() {
         break;
      }

      vertex = parent[vertex].unwrap();
   }

   path.reverse();

   writeln!(writer, "{} {}", dist[t].unwrap(), path.len() - 1).ok();

   for i in 1..path.len() {
      writeln!(writer, "{} {}", path[i - 1], path[i]).ok();
   }
}
