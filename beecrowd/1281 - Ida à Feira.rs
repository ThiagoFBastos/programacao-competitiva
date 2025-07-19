#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::*;
use std::collections::*;
use std::hash::Hash;

struct Scanner {
   buffer : VecDeque<String>,
   eof: bool
}
 
impl Scanner {
 
   fn new() -> Scanner {
      Scanner {
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
            Err(e) => panic!("panico {}", e)
         };

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
      };

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

    for _i in 0..tests {

        let mut map: HashMap<String, f64> = HashMap::new();

        let m = sc.next::<usize>();

        for _j in 0..m {

            let item = sc.next::<String>();
            let price = sc.next::<f64>();

            map.insert(item, price);
        }

        let p = sc.next::<usize>();

        let mut total_price: f64 = 0.0;

        for _j in 0..p {

            let item = sc.next::<String>();
            let quantity = sc.next::<i32>();

            let price = map.get(&item).unwrap();

            total_price += (quantity as f64) * price;
        }

        println!("R$ {:.2}", total_price);
    }
}