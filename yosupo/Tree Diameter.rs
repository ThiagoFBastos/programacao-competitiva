/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-17
 */

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

   let mut adj = vec![vec![]; n];

   for _ in 1..n {
      let u = sc.next::<usize>().unwrap();
      let v = sc.next::<usize>().unwrap();
      let w = sc.next::<i64>().unwrap();

      adj[u].push((v, w));
      adj[v].push((u, w));
   }

   let farthest_node = |src: usize| {
      let mut dist = vec![None; n];
      let mut parent = vec![None; n];
      let mut queue = VecDeque::new();
      
      dist[src] = Some(0);
      queue.push_back(src);

      while !queue.is_empty() {
         let u = queue.pop_front().unwrap();

         for &(v, w) in adj[u].iter() {
            if dist[v].is_some() {
               continue;
            }

            parent[v] = Some(u);
            dist[v] = Some(w + dist[u].unwrap());
            queue.push_back(v);
         }
      }

      let target = (0..n).map(|v| (dist[v], v)).max();

      let (_, v) = target.unwrap();

      let mut path = Vec::new();
      let mut vertex = v;

      loop {
         path.push(vertex);

         if parent[vertex].is_none() {
            break;
         }

         vertex = parent[vertex].unwrap();
      }

      path.reverse();

      return (v, path, dist[v].unwrap());
   };

   let (v, _, _) = farthest_node(0);
   let (_, path, dist) = farthest_node(v);

   writeln!(writer, "{} {}", dist, path.len()).ok();

   for v in path {
      write!(writer, "{} ", v).ok();
   }

   write!(writer, "\n").ok();
}