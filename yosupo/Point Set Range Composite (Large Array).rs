/*
 * Author: Thiago Felipe Bastos da Silva
 * Created: 2026-01-20
 */

#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};
use std::ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Neg, Sub, SubAssign};

use crate::Queries::*;

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

   fn composite(&self, other: &Self) -> Self {

      Self {
         a: self.a * other.a,
         b: self.a * other.b + self.b
      }
   }

   fn evaluate(&self, x: i64) -> ModNumber<MOD> {
      self.a * ModNumber::new(x) + self.b
   }
}

impl<const MOD: i64> Default for Function<MOD> {
   fn default() -> Self {
       return Function::new(1, 0);
   }
} 

pub struct SegTree<T, OP> where OP: Fn(T, T) -> T {
   data: Vec<T>, // the segment tree data
   size: usize, // the number of elements
   op: OP // the binary operator
}

impl<T: Copy + Default, OP> SegTree<T, OP> where OP: Fn(T, T) -> T {

   /**
   * Create a new instance of SegTree
   * @param values the initial array of elements
   * @param op the binary operator
   */
   pub fn new(values: &[T], op: OP) -> Self {
      let n = values.len();

      let mut st = Self {
         data: vec![T::default(); 4 * n],
         size: n,
         op
      };

      st.build(values, 0, n - 1, 1);

      return st;
   }

   /**
    * Build the segment tree
      * @param values the initial array of elements
      * @param lo the leftmost position of the current range node
      * @param hi the rightmost position of the current range node
      * @param p the current node 
      */
   fn build(&mut self, values: &[T], lo: usize, hi: usize, p: usize) {
      if lo == hi {
         self.data[p] = values[lo];
         return;
      }

      let mid = (lo + hi) / 2;

      self.build(values, lo, mid, 2 * p);
      self.build(values, mid + 1, hi, 2 * p + 1);

      self.data[p] = (self.op)(self.data[2 * p], self.data[2 * p + 1]);
   }

   /**
    * Update the value at a specific position
      * @param k the position to update
      * @param value the value that will replace the old one
      * @param lo the leftmost position of the current range node
      * @param hi the rightmost position of the current range node
      * @param p the current node 
      */
   fn change(&mut self, k: usize, value: T, lo: usize, hi: usize, p: usize) {
      if lo == hi {
         self.data[p] = value;
         return;
      }

      let mid = (lo + hi) / 2;

      if k <= mid {
         self.change(k, value, lo, mid, 2 * p);
      } else {
         self.change(k, value, mid + 1, hi, 2 * p + 1);
      }

      self.data[p] = (self.op)(self.data[2 * p], self.data[2 * p + 1]);
   }

   /**
    * Find the value of an operation over a range
      * @param l the leftmost position of the target range
      * @param r the rightmost position of the target range
      * @param lo the leftmost position of the current range node
      * @param hi the rightmost position of the current range node
      * @param p the current node 
      */
   fn answer(&self, l: usize, r: usize, lo: usize, hi: usize, p: usize) -> T {
      if lo >= l && hi <= r {
         return self.data[p];
      }

      let mid = (lo + hi) / 2;

      if r <= mid {
         return self.answer(l, r, lo, mid, 2 * p);
      } else if l > mid {
         return self.answer(l, r, mid + 1, hi, 2 * p + 1);
      }

      let res1 = self.answer(l, r, lo, mid, 2 * p);
      let res2 = self.answer(l, r, mid + 1, hi, 2 * p + 1);

      return (self.op)(res1, res2);
   }

   /**
    * Update the value at a specific position
      * @param k the position to update
      * @param value the value that will replace the old one
      */
   pub fn update(&mut self, k: usize, value: T) {
      assert!(k < self.size);
      self.change(k, value, 0, self.size - 1, 1);
   }

   /**
    * Find the value of an operation over a range
      * @param l the leftmost position of the target range
      * @param r the rightmost position of the target range
      */
   pub fn query(&self, l: usize, r: usize) -> T {
      assert!(l <= r && r < self.size);
      return self.answer(l, r, 0, self.size - 1, 1);
   }
}

enum Queries {
   Update(usize, i64, i64),
   Query(usize, usize, i64)
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   _  = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   let mut coords = Vec::with_capacity(2 * q);
   let mut queries = Vec::with_capacity(q);
   
   for _ in 0..q {
      let t = sc.next::<u8>().unwrap();

      match t {
         0 => {
            let p = sc.next::<usize>().unwrap();
            let c = sc.next::<i64>().unwrap();
            let d = sc.next::<i64>().unwrap();

            queries.push(Update(p, c, d));

            coords.push(p);
         },
         1 => {
            let l = sc.next::<usize>().unwrap();
            let r = sc.next::<usize>().unwrap() - 1;
            let x = sc.next::<i64>().unwrap();

            queries.push(Query(l, r, x));

            coords.push(l);
            coords.push(r);
         },
         _ => {
            panic!("wrong query type");
         }
      }
   }

   coords.sort();
   coords.dedup();

   let functions = vec![Function::<MOD>::new(1, 0); coords.len()];

   let composition = |a: Function<MOD>, b: Function<MOD>| {
      return b.composite(&a);
   };

   let mut st = SegTree::new(&functions, composition);

   let get_coord_position = |x| {
      coords.binary_search(&x).unwrap()
   };

   for q in queries {

      match q {
         Update(p, c, d) => {
            let index = get_coord_position(p);
            st.update(index, Function::new(c, d));
         },
         Query(l, r, x) => {
            let left = get_coord_position(l);
            let right = get_coord_position(r);

            let f = st.query(left, right);

            let answer = f.evaluate(x);
            
            writeln!(writer, "{}", answer.value()).ok();
         }
      }
   }
}
