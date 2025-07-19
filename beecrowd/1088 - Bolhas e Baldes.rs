#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::*;
use std::collections::*;

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

struct BIT {
    data: Vec<i32>,
    len: usize
}

impl BIT {

    fn new(n: usize) -> BIT {
        BIT {
            data: vec![0; n + 1],
            len: n
        }
    }

    fn query(&self, mut k: i32) -> i32 {
        let mut sum: i32 = 0;

        while k > 0 {
            sum += self.data[k as usize];
            k -= k & -k;
        }

        return sum;
    }

    fn update(&mut self, mut k: i32, value: i32) {

        while k as usize <= self.len {
            self.data[k as usize] += value;
            k += k & -k;
        }
    }

}

fn main() {
    let mut sc = Scanner::new();

    loop {

        let n = sc.next::<usize>();

        if n == 0 {
            break;
        }

        let mut inversions: i64 = 0;

        let mut bit = BIT::new(n);

        for i in 0..n {

            let a = sc.next::<i32>();

            inversions += i as i64 - bit.query(a) as i64;

            bit.update(a, 1);
        }

        if inversions % 2 == 1 {
            println!("Marcelo");
        } else {
            println!("Carlos");
        }
    }
}