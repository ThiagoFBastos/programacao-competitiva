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

struct BIT2D {
    data: Vec<Vec<i32>>,
    rows: usize,
    columns: usize
}

impl BIT2D {

    fn new(rows: usize, columns: usize) -> BIT2D {

        BIT2D { 
            data: vec![vec![0; columns + 1]; rows + 1], 
            rows: rows, 
            columns: columns 
        }
    }

    fn query(&self, mut x: i32, mut y: i32) -> i32 {
        x += 1;
        y += 1;

        if x < 0 || y < 0 {
            panic!("somente indices não negativos são aceitos");
        }

        let mut answer = i32::default();

        while x > 0 {
            let mut k = y;

            while k > 0 {
                answer += self.data[x as usize][k as usize];
                k -= k & -k;
            }

            x -= x & -x;
        }

        return answer;
    }

    fn calculate(&self, x0: i32, y0: i32, x1: i32, y1: i32) -> i32 {
        return self.query(x1, y1) - self.query(x1, y0 - 1) - self.query(x0 - 1, y1) + self.query(x0 - 1, y0 - 1);
    }

    fn update(&mut self, mut x: i32, mut y: i32, value: i32) {
        x += 1;
        y += 1;

        if x < 0 || y < 0 {
            panic!("somente indices não negativos são aceitos");
        }

        while x as usize  <= self.rows {

            let mut k = y;

            while k as usize <= self.columns {
                self.data[x as usize][k as usize] += value;
                k += k & -k;
            }

            x += x & -x;
        }
    }

}

fn main() {
    let mut sc = Scanner::new();

    loop {

        let x = sc.next::<usize>();
        let y = sc.next::<usize>();
        let p = sc.next::<i32>();

        if x == 0 && y == 0 && p == 0 {
            break;
        }

        let mut bit = BIT2D::new(x, y);

        let q = sc.next::<usize>();

        for _i in 0..q {

            let t = sc.next::<char>();

            if t == 'A' {
                let n = sc.next::<i32>();
                let x = sc.next::<i32>();
                let y = sc.next::<i32>();

                bit.update(x, y, n);
            } else {
                let mut x0 = sc.next::<i32>();
                let mut y0 = sc.next::<i32>();
                let mut x1 = sc.next::<i32>();
                let mut y1 = sc.next::<i32>();

                if x0 > x1 {
                    std::mem::swap(&mut x0, &mut x1);
                }

                if y0 > y1 {
                    std::mem::swap(&mut y0, &mut y1);
                }

                println!("{}", p * bit.calculate(x0, y0, x1, y1));
            }
        }

        print!("\n");
    }
}