#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::io::Write;
use std::ops::Add;
 
struct Scanner {
   buffer: VecDeque<String>
}
 
impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new()
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> T {
 
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

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();
 
   const CHUNK_SIZE: usize = 320;
   const MAXN: usize = 1 << 20;

   let mut count = vec![0; MAXN];

   let n = sc.next::<usize>();
   let m = sc.next::<usize>();
   let k = sc.next::<usize>();

   let mut prefix = vec![0; n + 1];

   for i in 1..=n {
      prefix[i] = sc.next::<usize>();
      prefix[i] ^= prefix[i - 1];
   }

   let mut queries = Vec::with_capacity(m);
   let mut answer = vec![0; m];

   for i in 0..m {
      let l = sc.next::<usize>() - 1;
      let r = sc.next::<usize>() - 1;

      queries.push((l, r, i));
   }

   queries.sort_by_key(|q| (q.0 / CHUNK_SIZE, q.1));

   let mut lo: i32 = 0;
   let mut hi: i32 = -1;
   let mut subarrays: i64 = 0;

   for &(l, r, pos) in queries.iter() {

      let i = l / CHUNK_SIZE;

      while hi <= r as i32 {
         hi += 1;
         subarrays += count[prefix[hi as usize] ^ k];
         count[prefix[hi as usize]] += 1;
      }

      while hi > (r + 1) as i32 {
         count[prefix[hi as usize]] -= 1;
         subarrays -= count[prefix[hi as usize] ^ k];
         hi -= 1;
      }

      while lo < l as i32 {
         count[prefix[lo as usize]] -= 1;
         subarrays -= count[prefix[lo as usize] ^ k];
         lo += 1;
      }

      answer[pos] = subarrays;

      while lo > (i * CHUNK_SIZE) as i32 {
         lo -= 1;
         subarrays += count[prefix[lo as usize] ^ k];
         count[prefix[lo as usize]] += 1;
      }
   }

   for value in answer.iter() {
      writeln!(handle, "{}", value).ok();
   }

}
