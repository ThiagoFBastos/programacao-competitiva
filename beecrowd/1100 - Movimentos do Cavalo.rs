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

fn knight_moves(p0: &str, p1: &str) -> usize {
   const N: usize = 8;

   let x0 = p0.chars().nth(0).unwrap() as usize - 'a' as usize;
   let y0 = p0.chars().nth(1).unwrap() as usize - '1' as usize;
   let x1 = p1.chars().nth(0).unwrap() as usize - 'a' as usize;
   let y1 = p1.chars().nth(1).unwrap() as usize - '1' as usize;
   
   let mut distance = [[None; N]; N];

   let mut queue = VecDeque::new();

   let mut delta = Vec::new();

   for dx in 1..=2 {
      for dy in 1..=2 {
         if dx * dx + dy * dy == 5 {
            for &a in &[-1, 1] {
               for &b in &[-1, 1] {
                  delta.push((dx * a, dy * b));
               }
            }
         }
      }
   }

   queue.push_back((x0, y0));
   distance[x0][y0] = Some(0);

   while !queue.is_empty() {
      let (x, y) = queue.pop_front().unwrap();

      for &(dx, dy) in &delta {
         let xdest = x as i32 + dx;
         let ydest = y as i32 + dy;

         if xdest < 0 || xdest >= N as i32 || ydest < 0 || ydest >= N as i32 || distance[xdest as usize][ydest as usize].is_some() {
            continue;
         }

         distance[xdest as usize][ydest as usize] = Some(distance[x][y].unwrap() + 1);
         queue.push_back((xdest as usize, ydest as usize));
      }
   }

   distance[x1][y1].unwrap()
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   loop {
      let start = sc.next::<String>();

      if start.is_err() {
         break;
      }

      let ending = sc.next::<String>();

      let p0 = start.unwrap();
      let p1 = ending.unwrap();

      writeln!(writer, "To get from {} to {} takes {} knight moves.", p0, p1, knight_moves(&p0, &p1)).ok();
   }
}