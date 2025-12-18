#![allow(unused_imports)]
#![allow(dead_code)]
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

   const MOD: i32 = 1_000_000_007;

   let n = sc.next::<usize>().unwrap();
   let m = sc.next::<usize>().unwrap();
   let s = sc.next::<usize>().unwrap() - 1;
   let t = sc.next::<usize>().unwrap() - 1;

   let mut adj = vec![vec![]; n];

   for _ in 0..m {
      let u = sc.next::<usize>().unwrap() - 1;
      let v = sc.next::<usize>().unwrap() - 1;

      adj[u].push(v);
      adj[v].push(u);
   }

   let mut dist = vec![vec![-1; 2]; n];
   let mut paths = vec![vec![0; 2]; n];
   let mut queue = VecDeque::new();

   queue.push_back((s, 0));
   dist[s][0] = 0;
   paths[s][0] = 1;

   while !queue.is_empty() {
      let (u, k) = queue.pop_front().unwrap();

      if k == 0 {
         for &v in adj[u].iter() {
            if dist[v][0] != -1 {
               if dist[u][0] + 1 == dist[v][0] {
                  paths[v][0] += paths[u][0];

                  if paths[v][0] >= MOD {
                     paths[v][0] -= MOD;
                  }
               }
            } else {
               dist[v][0] = 1 + dist[u][0];
               paths[v][0] = paths[u][0];
               queue.push_back((v, 0));
            }

            if dist[u][0] == dist[v][0] {
               if dist[v][1] != -1 {
                  paths[v][1] += paths[u][0];

                  if paths[v][1] >= MOD {
                     paths[v][1] -= MOD;
                  }

                  continue;
               }

               dist[v][1] = 1 + dist[u][0];
               paths[v][1] = paths[u][0];
               queue.push_back((v, 1));
            }
         }
      } else {

         for &v in adj[u].iter() {
            if dist[v][1] != -1 {
               if dist[u][1] + 1 == dist[v][1] {
                  paths[v][1] += paths[u][1];

                  if paths[v][1] >= MOD {
                     paths[v][1] -= MOD;
                  }
               }
               continue;
            }

            dist[v][1] = 1 + dist[u][1];
            paths[v][1] = paths[u][1];
            queue.push_back((v, 1));
         }
      }
   }

   writeln!(handle, "{}", paths[t][1]).ok();
}  
