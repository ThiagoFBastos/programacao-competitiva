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

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   const MOD: i64 = 1_000_000_007;
   const MAXN: usize = 1_010;

   let n = sc.next::<usize>().unwrap();

   let mut dp = [[[ModNumber::<MOD>::new(0); MAXN]; 2]; 2];

   dp[0][0][0] = ModNumber::<MOD>::new(1);

   for i in 2..=n {

      for k in 0..2 {
         for j in 0..=n {
            dp[1][k][j] = ModNumber::new(0);
         }
      }

      for j in 0..=n {
         dp[1][1][j + 1] = dp[1][1][j + 1] + ModNumber::new(2) * dp[0][0][j];

         if j > 0 {
            dp[1][0][j - 1] = dp[1][0][j - 1] + ModNumber::new(j as i64) * dp[0][0][j];
         }

         dp[1][0][j] = dp[1][0][j] + ModNumber::new(0.max(i as i32 - j as i32 - 2) as i64) * dp[0][0][j];

         dp[1][1][j] = dp[1][1][j] + dp[0][1][j];

         dp[1][1][j + 1] = dp[1][1][j + 1] + dp[0][1][j];

         if j > 0 {
            dp[1][0][j - 1] = dp[1][0][j - 1] + ModNumber::new(j as i64 - 1) * dp[0][1][j];
         }

         dp[1][0][j] = dp[1][0][j] + ModNumber::new(0.max(i as i32 - j as i32 - 1) as i64) * dp[0][1][j];
      }

      dp.swap(0, 1);
   }

   writeln!(writer, "{}", dp[0][0][0].value()).ok();
}
