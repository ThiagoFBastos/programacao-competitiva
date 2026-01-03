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

         if initial.abs() >= 2 * MOD {
            initial %= MOD;
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

   let str = sc.next::<String>().unwrap().chars().collect::<Vec<_>>();
   
   let n = str.len();
   let mut frequency = vec![0; 26];

   for &ch in str.iter() {
      frequency[ch as usize - 'a' as usize] += 1;
   }

   if 2 * frequency.iter().max().unwrap() - 1 > n {
      writeln!(writer, "0").ok();
      return;
   }

   const MOD: i64 = 1_000_000_007;
   const N: usize = 5_010;

   let mut fat = [ModNumber::<MOD>::new(1); 2 * N];
   let mut inv = [ModNumber::<MOD>::new(1); 2 * N];
   let mut inv_fat = [ModNumber::<MOD>::new(1); 2 * N];
   let mut dp = [[ModNumber::<MOD>::new(0); N]; 2];

   for i in 2..=2*n {
      fat[i] = fat[i - 1] * ModNumber::new(i as i64);
      inv[i] = inv[MOD as usize % i] * ModNumber::new(MOD - MOD / i as i64);
      inv_fat[i] = inv_fat[i - 1] * inv[i];
   }

   let combination = |n, k| {
      return fat[n] * inv_fat[k] * inv_fat[n - k];
   };

   let mut total = 0;
   let mut cur = 0;

   dp[0][0] = ModNumber::<MOD>::new(1);

   for k in 0..26 {

      if frequency[k] == 0 {
         continue;
      }

      dp[cur ^ 1].fill(ModNumber::<MOD>::new(0));

      for i in 0..=total {

         for j in 1..=frequency[k] {
            let groups = fat[frequency[k]] * combination(frequency[k] - 1, j - 1);
            let merges = combination(i + j, j);
            let ways = dp[cur][i] * groups * merges;

            if (frequency[k] - j) % 2 == 0 {
               dp[cur ^ 1][i + j] += ways;
            } else {
               dp[cur ^ 1][i + j] -= ways;
            }
         }
      }

      total += frequency[k];
      cur ^= 1;
   }

   let mut answer = ModNumber::<MOD>::new(0);

   for i in 0..=n {
      answer += dp[cur][i];
   }

   for i in 0..26 {
      answer = answer * inv_fat[frequency[i]];
   }

   writeln!(writer, "{}", answer.value()).ok();
}
