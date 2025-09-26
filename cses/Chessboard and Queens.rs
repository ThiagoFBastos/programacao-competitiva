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

struct Queen {
   table: [[char; 8]; 8],
   line: [i32; 8],
   first_diagonal: [i32; 15],
   second_diagonal: [i32; 15],
   count: i32
}

impl Queen {

   fn new() -> Self {
      Self {
         table: [['\0'; 8]; 8],
         line: [0; 8],
         first_diagonal: [0; 15],
         second_diagonal: [0; 15],
         count: 0
      }
   }

   fn place(&mut self, x: usize, y: usize, ch: char) {
      self.table[x][y] = ch;
   }

   fn backtracking(&mut self, y: usize) {
      if y == 8 {
         self.count += 1;
         return;
      }

      for x in 0..8 {
         if self.table[x][y] == '.' && self.line[x] == 0 && self.first_diagonal[x + y] == 0 && self.second_diagonal[7 - y + x] == 0 {
            self.line[x] = 1;
            self.first_diagonal[x + y] = 1;
            self.second_diagonal[7 - y + x] = 1;
            self.backtracking(y + 1);
            self.line[x] = 0;
            self.first_diagonal[x + y] = 0;
            self.second_diagonal[7 - y + x] = 0;
         }
      }
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let mut queen = Queen::new();

   for i in 0..8 {
      let line = sc.next::<String>().ok().unwrap().chars().collect::<Vec<_>>();

      for j in 0..8 {
         queen.place(i, j, line[j]);
      }
   }

   queen.backtracking(0);

   writeln!(handle, "{}", queen.count).ok();
 }