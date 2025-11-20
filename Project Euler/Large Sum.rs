#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::ops::Add;

struct Scanner {
   buffer: VecDeque<String>
}

impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new()
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
 
      if self.buffer.is_empty() {
         let mut input = String::new();
         
         match std::io::stdin().read_line(&mut input) {
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
      }
 
      if self.buffer.is_empty() {
         self.buffer.push_back("".to_string());
      }

      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

#[derive(Clone, Debug)]
struct Bignumber {
   data: Vec<u8>
}

impl Bignumber {

   fn new(number: &String) -> Self {

      Self{
         data: number.chars().map(|c| c.to_digit(10).unwrap() as u8).collect::<Vec<u8>>()
      }
   }

   fn from_vec_u8(number: &Vec<u8>) -> Self {

      Self {
         data: number.clone()
      }
   }

   fn to_string(&self) -> String {
      self.data.iter().map(|digit| (*digit + '0' as u8) as char).collect::<String>()
   }
}

impl Add for Bignumber {
   type Output = Self;

   fn add(self, rhs: Self) -> Self::Output {
      let n = self.data.len();
      let m = rhs.data.len();

      let mut result = Vec::with_capacity(n.max(m) + 1);

      let mut i = n as i32 - 1;
      let mut j = m as i32 - 1;
      let mut carry = 0;

      while i >= 0 && j >= 0 {   
         let sum = self.data[i as usize] + rhs.data[j as usize] + carry;
         result.push(sum % 10);
         carry = sum / 10;
         i -= 1;
         j -= 1;
      }

      while i >= 0 {
         let sum = self.data[i as usize] + carry;
         result.push(sum % 10);
         carry = sum / 10;
         i -= 1;
      }

      while j >= 0 {   
         let sum = rhs.data[j as usize] + carry;
         result.push(sum % 10);
         carry = sum / 10;
         j -= 1;
      }

      if carry > 0 {
         result.push(carry);
      }

      result.reverse();

      Self::from_vec_u8(&result)
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   const N: usize = 100;

   let mut numbers = Vec::new();

   for _ in 0..N {
      let str = sc.next::<String>().ok().unwrap();

      numbers.push(Bignumber::new(&str));
   }

   let mut result = Bignumber::new(&"0".to_string());

   for number in numbers.iter() {
      result = result + number.clone();
   }

   let str = result.to_string();

   writeln!(handle, "{}", &str[0..10]).ok();
}
