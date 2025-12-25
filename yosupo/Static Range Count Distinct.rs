#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, HashMap};
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

struct FenwickTree {
   sum: Vec<i32>,
   len: usize
}

impl FenwickTree {

   fn new(len: usize) -> Self {

      Self {
         sum: vec![0; len + 1],
         len
      }
   }

   fn query(&self, mut k: i32) -> i32 {
      let mut answer = 0;

      while k > 0 {
         answer += self.sum[k as usize];
         k -= k & -k;
      }

      answer
   }

   fn update(&mut self, mut k: i32, value: i32) {
      
      while k <= self.len as i32 {
         self.sum[k as usize] += value;
         k += k & -k;
      }
   }
}

fn main() {
   let stdout = io::stdout();
   let mut handle = io::BufWriter::new(stdout);

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   if n == 0 {
      _ = sc.next::<String>();
   }

   let arr = (0..n).map(|_| sc.next::<i32>().unwrap()).collect::<Vec<_>>();

   let mut next = vec![-1; n];

   let mut position = HashMap::new();

   let mut ft = FenwickTree::new(n);

   for i in (0..n).rev() {

      if let Some(&pos) = position.get(&arr[i]) {
         next[i] = pos as i32;
         ft.update(pos as i32 + 1, -1);
      }

      ft.update(i as i32 + 1, 1);
      position.insert(arr[i], i);
   }

   let mut queries = Vec::with_capacity(q);
   let mut answer = vec![0; q];
   let mut lo = 0;

   for i in 0..q {
      let l = sc.next::<usize>().unwrap();
      let r = sc.next::<usize>().unwrap();
      
      if l < r {
         queries.push((l, r - 1, i));
      }
   }

   queries.sort();

   for i in 0..n {

      while lo < queries.len() && queries[lo].0 == i {
         let (l, r, pos) = queries[lo];

         answer[pos] = ft.query(r as i32 + 1) - ft.query(l as i32);
         lo += 1;
      }

      if next[i] != -1 {
         ft.update(next[i] + 1, 1);
      }
   }

   for value in &answer {
      writeln!(handle, "{}", value).ok();
   }
}
