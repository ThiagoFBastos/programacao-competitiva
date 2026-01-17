/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-17
 */

#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};
use std::ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Neg, Sub, SubAssign};

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

   fn read_line(&mut self) -> io::Result<String> {
       let mut input = String::new();

      match self.reader.read_line(&mut input) {
         Ok(0) => {
            return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
         } Ok(_) => {
            
         } Err(e) => {
            return Err(e);
         }
      }

      Ok(input)
   }
}

#[derive(Clone, Copy, PartialEq)]
pub struct ModNumber<const MOD: i64> {
    number: i64 // number (mod MOD)
}

impl<const MOD: i64> ModNumber<MOD> {

    /**
     * Create a new instance of ModNumber
     * @param initial the value that will be stored
     */
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

    /**
     * Return the value of number (mod MOD)
     */
    pub fn value(&self) -> i64 {
        self.number
    }

    /**
     *  Return the stored number raised to the power of n
     */  
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

// operator +
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

// operator -
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

// operator *  
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

// operator /   
impl<const MOD: i64> Div for ModNumber<MOD> {
    type Output = Self;

    fn div(self, rhs: Self) -> Self::Output {
        self * rhs.pow(MOD as u64 - 2)
    }
}

// operator -val
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

// operator +=
impl<const MOD: i64> AddAssign for ModNumber<MOD> {

    fn add_assign(&mut self, rhs: Self) {
        *self = *self + rhs;
    }
}

// operator -=
impl<const MOD: i64> SubAssign for ModNumber<MOD> {   

    fn sub_assign(&mut self, rhs: Self) {
        *self = *self - rhs;
    }
}

// operator *=
impl<const MOD: i64> MulAssign for ModNumber<MOD> {

    fn mul_assign(&mut self, rhs: Self) {
        *self = *self * rhs;
    }
}

// operator /=
impl<const MOD: i64> DivAssign for ModNumber<MOD> {

    fn div_assign(&mut self, rhs: Self) {
        *self = *self / rhs;
    }
}

const MOD: i64 = 998244353;

#[derive(Clone, Copy)]
struct FunctionMod<const MOD: i64> {
   dx: ModNumber<MOD>,
   dy: ModNumber<MOD>
}

impl<const MOD: i64> FunctionMod<MOD> {

   fn new(a: i64, b: i64) -> Self {

      Self {
         dx: ModNumber::<MOD>::new(a),
         dy: ModNumber::<MOD>::new(b)
      }
   }
}

impl<const MOD: i64> Mul for FunctionMod<MOD> {

   type Output = Self;

   fn mul(self, rhs: Self) -> Self::Output {
      return FunctionMod {dx: self.dx * rhs.dx, dy: self.dx * rhs.dy + self.dy};
   }
}

struct LazySegTree {
   sum: Vec<ModNumber<MOD>>,
   lazy: Vec<FunctionMod<MOD>>,
   marked: Vec<bool>,
   size: usize
}

impl LazySegTree {

   fn build(&mut self, values: &[ModNumber<MOD>], lo: usize, hi: usize, p: usize) {
      if lo == hi {
         self.sum[p] = values[lo];
         return;
      }

      let mid = (lo + hi) >> 1;

      self.build(values, lo, mid, p << 1);
      self.build(values, mid + 1, hi, (p << 1) | 1);

      self.sum[p] = self.sum[p << 1] + self.sum[(p << 1) | 1];
   }

   fn new(values: &[ModNumber<MOD>]) -> Self {

      let n = values.len();

      let mut st = Self {
         sum: vec![ModNumber::new(0); 4 * n],
         lazy: vec![FunctionMod::new(1, 0); 4 * n],
         marked: vec![false; 4 * n],
         size: n
      };

      st.build(values, 0, n - 1, 1);

      st
   }

   fn push(&mut self, p: usize, l: usize, r: usize) {
      if !self.marked[p] {
         return;
      }

      for i in 0..2 {
         let q = (p << 1) | i;
         let len = (r - l + 2 - i) >> 1;
         self.sum[q] = self.lazy[p].dx * self.sum[q] + ModNumber::new(len as i64) * self.lazy[p].dy;
         self.lazy[q] = self.lazy[p] * self.lazy[q];
         self.marked[q] = true;
      }

      self.lazy[p] = FunctionMod::new(1, 0);
      self.marked[p] = false;
   }

   fn update(&mut self, f: FunctionMod<MOD>, l: usize, r: usize, lo: usize, hi: usize, p: usize) {
      if r < lo || l > hi {
         return;
      } else if lo >= l && hi <= r {
         self.sum[p] = f.dx * self.sum[p] + ModNumber::new(hi as i64 - lo as i64 + 1) * f.dy;
         self.lazy[p] = f * self.lazy[p];
         self.marked[p] = true;
         return;
      }

      let mid = (lo + hi) >> 1;

      self.push(p, lo, hi);
      self.update(f, l, r, lo, mid, p << 1);
      self.update(f, l, r, mid + 1, hi, (p << 1) | 1);

      self.sum[p] = self.sum[p << 1] + self.sum[(p << 1) | 1];
   }

   fn query(&mut self, l: usize, r: usize, lo: usize, hi: usize, p: usize) -> ModNumber<MOD> {
      if r < lo || l > hi {
         return ModNumber::new(0);
      } else if lo >= l && hi <= r {
         return self.sum[p];
      }

      let mid = (lo + hi) >> 1;

      self.push(p, lo, hi);
      
      let left = self.query(l, r, lo, mid, p << 1);
      let right = self.query(l, r, mid + 1, hi, (p << 1) | 1);

      return left + right;
   }
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let values = (0..n).map(|_| ModNumber::<MOD>::new(sc.next::<i64>().unwrap())).collect::<Vec<_>>();

   let mut st = LazySegTree::new(&values);

   for _ in 0..q {
      let t = sc.next::<u8>().unwrap();
      let l = sc.next::<usize>().unwrap();
      let r = sc.next::<usize>().unwrap() - 1;

      if t == 0 {
         let b = sc.next::<i64>().unwrap();
         let c = sc.next::<i64>().unwrap();
         st.update(FunctionMod::new(b, c), l, r, 0, n - 1, 1);
      } else {
         let answer = st.query(l, r, 0, n - 1, 1);
         writeln!(writer, "{}", answer.value()).ok();
      }
   }
}