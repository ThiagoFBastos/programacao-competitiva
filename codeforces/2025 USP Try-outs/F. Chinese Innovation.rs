#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::Reverse;
use std::collections::{BinaryHeap, VecDeque};
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
               return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
            } Ok(_) => {
               
            } Err(e) => {
               return Err(e);
            }
         }
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();
      }

      if self.buffer.is_empty() {
         self.buffer.push_back("".to_string());
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let m = sc.next::<usize>().unwrap();
   let k = sc.next::<usize>().unwrap();

   let mut adj = vec![vec![]; n + k];

   for _ in 0..m {
      let u = sc.next::<usize>().unwrap() - 1;
      let v = sc.next::<usize>().unwrap() - 1;
      let cost = sc.next::<i64>().unwrap();

      adj[u].push((v, cost));
      adj[v].push((u, cost));
   }

   for v in 0..n {
      let t = sc.next::<usize>().unwrap();

      for _ in 0..t {
         let u = sc.next::<usize>().unwrap() - 1;
         let cost = sc.next::<i64>().unwrap();

         adj[v].push((u + n, cost));
         adj[u + n].push((v, 0));
      }
   }

   let mut pq = BinaryHeap::new();
   let mut cost = vec![-1; n + k];

   pq.push(Reverse((0, 0)));

   while !pq.is_empty() {

      let (cst, u) = pq.pop().unwrap().0;

      if cost[u] != -1 {
         continue;
      }

      cost[u] = cst;

      if u == n - 1 {
         break;
      }

      for (v, w) in adj[u].iter() {

         let total_cost = cst + *w;

         if cost[*v] != -1 {
            continue;
         }

         pq.push(Reverse((total_cost, *v)));
      }
   }

   writeln!(handle, "{}", cost[n - 1]).ok();
 }
