#![allow(unused_imports)]
use std::collections::VecDeque;
use std::io::Write;

struct Scanner {
   buffer : VecDeque<String>
}
 
impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new()
      }
   }
   
   fn next<T : std::str::FromStr>(&mut self) -> T {
 
      if self.buffer.is_empty() {
         let mut input = String::new();
         
         std::io::stdin().read_line(&mut input).ok();
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      front.parse::<T>().ok().unwrap()
   }
}

struct UnionFind {
   parent: Vec<usize>,
   rank: Vec<u32>
}

impl UnionFind {

   fn new(n: usize) -> Self {

      let parent: Vec<usize> = (0..n).collect();
      let rank= vec![0 as u32; n];

      Self {
         parent: parent,
         rank: rank
      }
   }

   fn find_set(&mut self, u: usize) -> usize {

      self.parent[u] = if u == self.parent[u] { u } else { self.find_set(self.parent[u]) };

      return self.parent[u];
   }

   fn unite(&mut self, mut u: usize, mut v: usize) -> bool {

      u = self.find_set(u);
      v = self.find_set(v);

      if u == v {
         return false;
      } else if self.rank[u] > self.rank[v] {
         std::mem::swap(&mut u, &mut v);
      }

      self.parent[u] = v;
      self.rank[v] = if self.rank[u] == self.rank[v] { self.rank[v] + 1 } else { self.rank[v] };

      return true;
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);

   let mut sc = Scanner::new();

   let n = sc.next::<usize>();
   let m = sc.next::<usize>();

   let mut uf = UnionFind::new(n);

   let mut graph = Vec::with_capacity(m);

   for _ in 0..m {
      let u = sc.next::<usize>() - 1;
      let v = sc.next::<usize>() - 1;
      let w = sc.next::<i32>();

      graph.push((u, v, w));
   }

   graph.sort_by_key(|e| e.2);

   let mut total_cost = i64::default();
   let mut components = n;

   for &(u, v, w) in graph.iter() {

      if uf.unite(u, v) {
         components -= 1;
         total_cost += w as i64;
      }
   }

   if components == 1 {
      writeln!(handle, "{total_cost}").ok();
   } else {
      writeln!(handle, "IMPOSSIBLE").ok();
   }
}
