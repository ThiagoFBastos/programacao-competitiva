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
   rank: Vec<u32>,
   size: Vec<u32>
}
 
impl UnionFind {
 
   fn new(n: usize) -> Self {
 
      let parent: Vec<usize> = (0..n).collect();
      let rank= vec![0 as u32; n];
      let size = vec![1 as u32; n];
 
      Self {
         parent: parent,
         rank: rank,
         size: size
      }
   }
 
   fn find_set(&mut self, u: usize) -> usize {
 
      self.parent[u] = if u == self.parent[u] { u } else { self.find_set(self.parent[u]) };
 
      return self.parent[u];
   }
 
   fn unite(&mut self, mut u: usize, mut v: usize) -> (bool, u32) {
 
      u = self.find_set(u);
      v = self.find_set(v);
 
      if u == v {
         return (false, self.size[u]);
      } else if self.rank[u] > self.rank[v] {
         std::mem::swap(&mut u, &mut v);
      }
 
      self.parent[u] = v;
      self.rank[v] = if self.rank[u] == self.rank[v] { self.rank[v] + 1 } else { self.rank[v] };
      self.size[v] += self.size[u];
 
      return (true, self.size[v]);
   }
}
 
fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
 
   let n = sc.next::<usize>();
   let m = sc.next::<usize>();
 
   let mut uf = UnionFind::new(n);
 
   let mut components = n as u32;
   let mut largest_component: u32 = 1;
 
   for _ in 0..m {
 
      let u = sc.next::<usize>() - 1;
      let v = sc.next::<usize>() - 1;
 
      let (state, length) = uf.unite(u, v);
 
      if state {
         components -= 1;
         largest_component = largest_component.max(length);
      }
 
      writeln!(handle, "{} {}", components, largest_component).ok();
   }
}
