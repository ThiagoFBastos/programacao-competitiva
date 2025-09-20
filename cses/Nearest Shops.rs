#![allow(unused_imports)]
use std::collections::{VecDeque};
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

struct Graph {
   adj: Vec<Vec<usize>>,
   n: usize
}

impl Graph {

   fn new(n: usize) -> Self {

      Self {
         adj: (0..n).map(|_| Vec::new()).collect(),
         n: n
      }
   }

   fn add_edge(&mut self, u: usize, v: usize) {
      self.adj[u].push(v);
      self.adj[v].push(u);
   }
}

trait Nearest {

   fn find_nearest_cities(&self, shops: &[usize]) -> Vec<i32>;
}

impl Nearest for Graph {

   fn find_nearest_cities(&self, shops: &[usize]) -> Vec<i32> {
      let mut dist = (0..2).map(|_| vec![(-1, -1); self.n]).collect::<Vec<Vec<(i32, i32)>>>();
      let mut queue = VecDeque::new();

      for &v in shops.iter() {
         queue.push_back((v, 0));
         dist[0][v] = (0, v as i32);
      }

      while !queue.is_empty() {

         let (v, k) = queue.pop_front().unwrap();

         for &u in self.adj[v].iter() {

            let (da1, a1) = dist[0][u];
            let (da2, _) = dist[1][u];
            let (db, b) = dist[k][v];

            if k == 0 {
               if da1 == -1 {
                  queue.push_back((u, 0));
                  dist[0][u] = (db + 1, b);
               } else if da2 == -1 && a1 != b {
                  queue.push_back((u, 1));
                  dist[1][u] = (db + 1, b);
               }
            } else if da2 == -1 && b != a1 {
               queue.push_back((u, 1));
               dist[1][u] = (db + 1, b);
            }
         }
      }

      let distance = (0..self.n).map(|v| {
         let (da1, a1) = dist[0][v];
         let (da2, _) = dist[1][v];

         if a1 == v as i32 {
            return da2;
         }

         return da1;
      }).collect::<Vec<i32>>();

      return distance;
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
   
   let n = sc.next::<usize>().ok().unwrap();
   let m = sc.next::<usize>().ok().unwrap();
   let k = sc.next::<usize>().ok().unwrap();

   let shops = (0..k).map(|_| sc.next::<usize>().ok().unwrap() - 1)
                     .collect::<Vec<usize>>();

   let mut graph = Graph::new(n);

   for _ in 0..m {
      let a = sc.next::<usize>().ok().unwrap() - 1;
      let b = sc.next::<usize>().ok().unwrap() - 1;

      graph.add_edge(a, b);
   }

   let distances = graph.find_nearest_cities(&shops);

   for d in distances.iter() {
      write!(handle, "{} ", d).ok();
   }

   write!(handle, "\n").ok();
}