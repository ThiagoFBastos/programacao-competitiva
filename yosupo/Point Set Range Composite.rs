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

#[derive(Copy, Clone)]
struct Function<const MOD: i64> {
   a: ModNumber<MOD>,
   b: ModNumber<MOD>
}

impl<const MOD: i64> Function<MOD> {

   fn new(a: i64, b: i64) -> Self {

      Self {
         a: ModNumber::new(a),
         b: ModNumber::new(b)
      }
   }
}

impl<const MOD: i64> Mul for Function<MOD> {
   type Output = Self;

   fn mul(self, rhs: Self) -> Self::Output {
       
       Self {
         a: self.a * rhs.a,
         b: self.a * rhs.b + self.b
       }
   }
}

struct SegTree {
   function: Vec<Function<MOD>>,
   size: usize
}

impl SegTree {

   fn build(&mut self, f: &[Function<MOD>], lo: usize, hi: usize, p: usize) {
      if lo == hi {
         self.function[p] = f[lo];
         return;
      }

      let mid = (lo + hi) >> 1;

      self.build(f, lo, mid, p << 1);
      self.build(f, mid + 1, hi, (p << 1) | 1);

      self.function[p] = self.function[(p << 1) | 1] * self.function[p << 1];
   }

   fn new(functions: &[Function<MOD>]) -> Self {

      let n = functions.len();

      let mut st = Self {
         function: vec![Function::new(0, 0); 4 * n],
         size: n
      };

      st.build(functions, 0, n - 1, 1);

      st
   }

   fn update(&mut self, k: usize, f: Function<MOD>, lo: usize, hi: usize, p: usize) {
      if lo == hi {
         self.function[p] = f;
         return;
      }

      let mid = (lo + hi) >> 1;

      if k <= mid {
         self.update(k, f, lo, mid, p << 1);
      } else {
         self.update(k, f, mid + 1, hi, (p << 1) | 1);
      }

      self.function[p] = self.function[(p << 1) | 1] * self.function[p << 1];
   }

   fn query(&self, l: usize, r: usize, lo: usize, hi: usize, p: usize) -> Function<MOD> {
      if r < lo || l > hi {
         return Function::new(1, 0);
      } else if lo >= l && hi <= r {
         return self.function[p];
      }

      let mid = (lo + hi) >> 1;

      let left = self.query(l, r, lo, mid, p << 1);
      let right = self.query(l, r, mid + 1, hi, (p << 1) | 1);

      return right * left;
   }

   fn set(&mut self, k: usize, f: Function<MOD>) {
      self.update(k, f, 0, self.size - 1, 1);
   }

   fn evaluate(&mut self, l: usize, r: usize, x: i64) -> ModNumber<MOD> {
      let f = self.query(l, r, 0, self.size - 1, 1);
      return f.a * ModNumber::new(x) + f.b;
   }
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let mut functions = Vec::with_capacity(n);

   for _ in 0..n {
      let a = sc.next::<i64>().unwrap();
      let b = sc.next::<i64>().unwrap();
      functions.push(Function::<MOD>::new(a, b));
   }

   let mut st = SegTree::new(&functions);

   for _ in 0..q {
      let t = sc.next::<u8>().unwrap();

      match t {
         0 => {
            let k = sc.next::<usize>().unwrap();
            let a = sc.next::<i64>().unwrap();
            let b = sc.next::<i64>().unwrap();

            st.set(k, Function::new(a, b));
         },
         1 => {
            let l = sc.next::<usize>().unwrap();
            let r = sc.next::<usize>().unwrap() - 1;
            let x = sc.next::<i64>().unwrap();

            let answer = st.evaluate(l, r, x);

            writeln!(writer, "{}", answer.value()).ok();
         },
         _ => {
            panic!("wrong query type");
         }
      }
   }
}