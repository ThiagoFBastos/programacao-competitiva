/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-18
 */

#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{BTreeSet, VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};
use std::ops::Bound::*;

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

   let mut adj = vec![vec![]; n + 1];

   for _ in 0..m {
      let u = sc.next::<usize>().unwrap() + 1;
      let v = sc.next::<usize>().unwrap() + 1;

      adj[u].push(v);
      adj[v].push(u);
   }

   for neighbourhood in adj.iter_mut() {
      neighbourhood.sort();
   }

   let mut unseen = BTreeSet::new();
   let mut components = Vec::new();

   for u in 1..=n {
      unseen.insert(u);
   }

   for u in 1..=n {
      if !unseen.contains(&u) {
         continue;
      }

      let mut queue = VecDeque::new();
      let mut component = Vec::new();

      unseen.remove(&u);
      queue.push_back(u);

      while !queue.is_empty() {
         let u = queue.pop_front().unwrap();

         component.push(u);

         let mut low = 1;

         adj[u].push(n + 1);

         for &v in adj[u].iter() {
            let length = queue.len();

            if low <= v - 1 {
               let mut it = unseen.range((Included(low), Included(v - 1)));
               
               loop {
                  let element = it.next();

                  if element.is_none() {
                     break;
                  }

                  queue.push_back(*element.unwrap());
               }
            }

            for i in length..queue.len() {
               unseen.remove(&queue[i]);
            }

            low = v + 1;
         }
      }

      components.push(component);
   }

   writeln!(writer, "{}", components.len()).ok();

   for cc in components.iter() {
      write!(writer, "{}", cc.len()).ok();

      for &v in cc.iter() {
         write!(writer, " {}", v - 1).ok();
      }

      write!(writer, "\n").ok();
   }
}
