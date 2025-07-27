#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, BTreeMap};

struct Scanner {
   buffer : VecDeque<String>,
   eof: bool
}
 
impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new(),
         eof: false
      }
   }
   
   fn next<T : std::str::FromStr + Default >(&mut self) -> T {
 
      if self.buffer.len() == 0 {
         let mut input = String::new();
         
         match std::io::stdin().read_line(&mut input) {
            Ok(0) => self.eof = true,
            Ok(_) => {},
            Err(e) => panic!("{}", e)
         }

         for word in input.split_whitespace() {
            self.buffer.push_back(word.to_string())
         }
      }

      if self.eof {
         return T::default();
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      front.parse::<T>().ok().unwrap()
   }

   fn read_line(&mut self) -> String {
      let mut input = String::new();
         
      match std::io::stdin().read_line(&mut input) {
         Ok(0) => self.eof = true,
         Ok(_) => {},
         Err(e) => panic!("{}", e)
      }

      if input.ends_with('\n') {
         input.pop();
         if input.ends_with('\r') {
            input.pop();
         }
      }

      return input;
   }

   fn is_eof(&self) -> bool {
      self.eof
   }
}

fn main() {
    let mut sc = Scanner::new();

    let tests = sc.next::<usize>();

    sc.read_line();

    for i in 0..tests {

      let mut trees: BTreeMap<String, usize> = BTreeMap::new();

      let mut n: usize = 0;

      loop {

         let specie = sc.read_line();

         if specie.is_empty() || sc.is_eof() {
            break;
         }

         if let Some(count) = trees.get(&specie) {
            trees.insert(specie, count + 1);
         } else {
            trees.insert(specie, 1);
         }

         n += 1;
      }

      if i > 0 {
         print!("\n");
      }

      for (specie, count) in trees.iter() {
         let percent = (*count as f64) / (n as f64);

         println!("{} {:.4}", specie, percent * 100.0);
      }
    }
}