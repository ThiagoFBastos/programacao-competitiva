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
   let stdout = io::stdout();
   let mut handle = io::BufWriter::new(stdout);

   let mut sc = Scanner::new();

   const MAXN: usize = 2500;

   let n = sc.next::<usize>().unwrap();
   let m = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let mut adj = vec![vec![]; n];

   for _ in 0..m {
      let u = sc.next::<usize>().unwrap() - 1;
      let v = sc.next::<usize>().unwrap() - 1;

      adj[u].push(v);
      adj[v].push(u);
   }

   let mut queries = vec![vec![]; n];
   let mut answer = vec![false; q];

   for i in 0..q {
      let a = sc.next::<usize>().unwrap() - 1;
      let b =  sc.next::<usize>().unwrap() - 1;
      let x =  sc.next::<i32>().unwrap();

      queries[a].push((b, x, i));
   }

   for v in 0..n {
      if queries[v].is_empty() {
         continue;
      }

      let mut dist = [[-1; 2]; MAXN];
      let mut queue = VecDeque::new();

      queue.push_back((v, 0));
      dist[v][0] = 0;

      while !queue.is_empty() {
         let (u, p) = queue.pop_front().unwrap();

         for &w in adj[u].iter() {
            if dist[w][p ^ 1] != -1 {
               continue;
            }

            dist[w][p ^ 1] = 1 + dist[u][p];
            queue.push_back((w, p ^ 1));
         }
      }

      for &(u, x, pos) in queries[v].iter() {
         let dab = dist[u][x as usize & 1];

         answer[pos] = dab != -1 && dab <= x;
      }
   }

   for status in answer.iter() {
      writeln!(handle, "{}", if *status { "YES" } else { "NO" }).ok();
   }
}
