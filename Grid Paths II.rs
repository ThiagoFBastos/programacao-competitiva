#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};

use crate::math::ModNumber;

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

pub mod math {
    use std::ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Neg, Sub, SubAssign};

   #[derive(Clone, Copy, PartialEq)]
   pub struct ModNumber<const MOD: i64> {
      number: i64
   }
   
   impl<const MOD: i64> ModNumber<MOD> {

      pub fn new(mut initial: i64) -> Self {
         assert!(MOD >= 2);

         if initial >= 2 * MOD {
            initial %= MOD;
         } else if initial < -MOD {
            initial = (initial % MOD + MOD) % MOD;
         } else if initial >= MOD {
            initial -= MOD;
         } else if initial < 0 {
            initial += MOD;
         }

         Self {
            number: initial
         }
      }

      pub fn value(&self) -> i64 {
         self.number
      }

      pub fn pow(&self, mut n: u64) -> Self {
         let mut result = Self::new(1);
         let mut number = self.clone();

         while n > 0 {

            if n & 1 == 1 {
               result = result * number;
            }

            number = number * number;

            n >>= 1;
         }

         result
      }
   }

   impl<const MOD: i64> Add for ModNumber<MOD> {
      type Output = Self;

      fn add(self, rhs: Self) -> Self::Output {
         let mut result = self.number + rhs.number;

         if result >= MOD {
            result -= MOD;
         }

         ModNumber::new(result)
      }
   }

   impl<const MOD: i64> Sub for ModNumber<MOD> {
      type Output = Self;

      fn sub(self, rhs: Self) -> Self::Output {
         let mut result = self.number - rhs.number;

         if result < 0 {
            result += MOD;
         }

         ModNumber::new(result)
      }
   }

   impl<const MOD: i64> Mul for ModNumber<MOD> {
      type Output = Self;

      fn mul(self, rhs: Self) -> Self::Output {

         let result = self.number.checked_mul(rhs.number);

         if result.is_none() {
            return ModNumber::new(((self.number as i128 * rhs.number as i128) % MOD as i128) as i64);
         }

         ModNumber::new(result.unwrap() % MOD)
      }
   }

   impl<const MOD: i64> Div for ModNumber<MOD> {
      type Output = Self;

      fn div(self, rhs: Self) -> Self::Output {
          self * rhs.pow(MOD as u64 - 2)
      }
   }

   impl<const MOD: i64> Neg for ModNumber<MOD> {
      type Output = Self;

      fn neg(mut self) -> Self::Output {
          self.number = MOD - self.number;

          if self.number >= MOD {
            self.number -= MOD;
          }

          self
      }
   }

   impl<const MOD: i64> AddAssign for ModNumber<MOD> {

      fn add_assign(&mut self, rhs: Self) {
          *self = *self + rhs;
      }
   }

   impl<const MOD: i64> SubAssign for ModNumber<MOD> {   

      fn sub_assign(&mut self, rhs: Self) {
         *self = *self - rhs;
      }
   }

   impl<const MOD: i64> MulAssign for ModNumber<MOD> {

      fn mul_assign(&mut self, rhs: Self) {
          *self = *self * rhs;
      }
   }

   impl<const MOD: i64> DivAssign for ModNumber<MOD> {

      fn div_assign(&mut self, rhs: Self) {
          *self = *self / rhs;
      }
   }
}

struct Combinatorics<const MOD: i64> {
   fat: Vec<ModNumber<MOD>>,
   inv: Vec<ModNumber<MOD>>,
   inv_fat: Vec<ModNumber<MOD>>
}

impl<const MOD: i64> Combinatorics<MOD> {

   fn new(n: usize) -> Self {

      let mut fat = vec![ModNumber::<MOD>::new(1); n];
      let mut inv = vec![ModNumber::<MOD>::new(1); n];
      let mut inv_fat = vec![ModNumber::<MOD>::new(1); n];

      for i in 2..n {
         fat[i] = fat[i - 1] * ModNumber::<MOD>::new(i as i64);
         inv[i] = inv[MOD as usize % i] * ModNumber::<MOD>::new(-MOD / i as i64);
         inv_fat[i] = inv_fat[i - 1] * inv[i];
      }

      Self {
         fat,
         inv,
         inv_fat
      }
   }

   fn combination(&self, n: usize, k: usize) -> ModNumber<MOD> {
      return self.fat[n] * self.inv_fat[k] * self.inv_fat[n - k];
   }
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   const MOD: i64 = 1_000_000_007;

   let n = sc.next::<usize>().unwrap();
   let m = sc.next::<usize>().unwrap();

   let cb = Combinatorics::<MOD>::new(2 * n + 1);
   let mut traps = Vec::with_capacity(m);
   let mut dp = Vec::with_capacity(m);
   
   for _ in 0..m {
      let x = sc.next::<usize>().unwrap();
      let y = sc.next::<usize>().unwrap();

      traps.push((x, y));
   }

   traps.sort();

   for &(x, y) in traps.iter() {
      dp.push(cb.combination(x + y - 2, x - 1));
   }

   for i in 0..m {
      let (x0, y0) = traps[i];

      for j in (i+1)..m {
         let (x1, y1) = traps[j];

         if y0 <= y1 {
            let count = dp[i] * cb.combination(x1 + y1 - x0 - y0, x1 - x0);
            dp[j] -= count;
         }
      }
   }

   let mut answer = cb.combination(2 * n - 2, n - 1);

   for i in 0..m {
      answer -= dp[i] * cb.combination(2 * n - traps[i].0 - traps[i].1, n - traps[i].0);
   }

   writeln!(writer, "{}", answer.value()).ok();
}
