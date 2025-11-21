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
   digits: Vec<u8>
}

impl Bignumber {

   fn new(str: &String) -> Self {

      Self {
         digits: str.chars().map(|c| c.to_digit(10).unwrap() as u8).collect()
      }
   }

   fn from_vec(digits: &Vec<u8>) -> Self {

      Self {
         digits: digits.clone()
      }
   }

   fn to_string(&self) -> String {
      self.digits.iter().map(|d| (*d + '0' as u8) as char).collect::<String>()
   }
}

impl Add for Bignumber {
   type Output = Self;

   fn add(self, rhs: Self) -> Self::Output {
      let n = self.digits.len();
      let m = rhs.digits.len();

      let mut result = Vec::with_capacity(n.max(m) + 1);

      let mut i = n as i32 - 1;
      let mut j = m as i32 - 1;
      let mut carry = 0;

       while i >= 0 && j >= 0 {
         let sum = self.digits[i as usize] + rhs.digits[j as usize] + carry;

         result.push(sum % 10);

         carry = sum / 10;

         i -= 1;
         j -= 1;
       }

       while i >= 0 {
         let sum = self.digits[i as usize] + carry;

         result.push(sum % 10);

         carry = sum / 10;

         i -= 1;
       }

       while j >= 0 {
         let sum = rhs.digits[j as usize] + carry;

         result.push(sum % 10);

         carry = sum / 10;

         j -= 1;
       }

       if carry > 0 {
         result.push(carry);
       }

       result.reverse();

       Self::from_vec(&result)
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();

   let mut num = Bignumber::new(&"1".to_string());

   for _  in 1..=n {
      num = num.clone() + num.clone();
   }

   let str = num.to_string();

   let sum = str.chars().map(|c| c.to_digit(10).unwrap()).sum::<u32>();

   writeln!(handle, "{}", sum).ok();
}
