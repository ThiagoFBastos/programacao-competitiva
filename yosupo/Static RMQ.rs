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
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

struct SparseTable<T> {
   st: Vec<Vec<T>>
}

impl<T: Default + Ord + Copy> SparseTable<T> {

   fn new(values: &[T]) -> Self {
      let n = values.len();
      
      if n == 0 {
         panic!("array is empty");
      }

      let k = 32 - (n as i32).leading_zeros() as usize;

      let mut st = vec![vec![T::default(); n]; k];

      for i in 0..n {
         st[0][i] = values[i];
      }

      for i in 1..k {
         for j in 0..n {
            if j + (1 << i) > n {
               break;
            }
            st[i][j] = st[i - 1][j].min(st[i - 1][j + (1 << (i - 1))]);
         }
      }

      Self {
         st: st
      }
   }

   fn query(&self, l: usize, r: usize) -> T {
      if l > r {
         panic!("interval has non positive size");
      }

      let log = 31 - ((r - l + 1) as i32).leading_zeros() as usize;

      self.st[log][l].min(self.st[log][r + 1 - (1 << log)])
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let q = sc.next::<usize>().ok().unwrap();

   let values = (0..n).map(|_| sc.next::<i32>().ok().unwrap()).collect::<Vec<_>>();

   let st = SparseTable::new(&values);

   for _ in 0..q {
      let l = sc.next::<usize>().ok().unwrap();
      let r = sc.next::<usize>().ok().unwrap();

      writeln!(handle, "{}", st.query(l, r - 1)).ok();
   }
 }
