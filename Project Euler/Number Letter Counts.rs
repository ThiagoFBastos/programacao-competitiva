#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque, BTreeMap};
use std::io::{self, Error, ErrorKind, Write};

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

fn number_to_speech(mut n: i32) -> String {
   let mut pieces = BTreeMap::new();
   let mut multipliers = BTreeMap::new();

   let mut speech = String::new();

   pieces.insert(1, "one");
   pieces.insert(2, "two");
   pieces.insert(3, "three");
   pieces.insert(4, "four");
   pieces.insert(5, "five");
   pieces.insert(6, "six");
   pieces.insert(7, "seven");
   pieces.insert(8, "eight");
   pieces.insert(9, "nine");
   pieces.insert(10, "ten");
   pieces.insert(11, "eleven");
   pieces.insert(12, "twelve");
   pieces.insert(13, "thirteen");
   pieces.insert(14, "fourteen");
   pieces.insert(15, "fifteen");
   pieces.insert(16, "sixteen");
   pieces.insert(17, "seventeen");
   pieces.insert(18, "eighteen");
   pieces.insert(19, "nineteen");
   pieces.insert(20, "twenty");
   pieces.insert(30, "thirty");
   pieces.insert(40, "forty");
   pieces.insert(50, "fifty");
   pieces.insert(60, "sixty");
   pieces.insert(70, "seventy");
   pieces.insert(80, "eighty");
   pieces.insert(90, "ninety");

   multipliers.insert(100, "hundred");
   multipliers.insert(1000, "thousand");

   for (value, text) in multipliers.iter().rev() {
      if n >= *value {
         let first_part = *pieces.get(&(n / *value)).unwrap();

         speech.push_str(&first_part);
         speech.push_str(" ");
         speech.push_str(*text);

         n %= *value;
      }
   }

   if n != 0 && !speech.is_empty() {
      speech.push_str(" and");
   }

   for (value, text) in pieces.iter().rev() {
      if n >= *value {
          if !speech.is_empty() {
            speech.push_str(" ");
         }

         speech.push_str(*text);
         n -= *value;
      }
   }

   speech
}

fn count_characters_in_interval(lo: i32, hi:i32) -> usize {
   let mut result = 0;

   for i in lo..=hi {
      let speech = number_to_speech(i);

      let chars = speech.chars().filter(|c| *c != ' ').count();

      result += chars;
   }

   result
}

#[cfg(test)]
mod tests {
   use super::*;

   #[test]
   fn test_123() {
      const N: i32 = 123;

      let speech = number_to_speech(N);

      assert_eq!(speech, "one hundred and twenty three");
   }

   #[test]
   fn test_1000() {
      const N: i32 = 1000;

      let speech = number_to_speech(N);

      assert_eq!(speech, "one thousand");
   }

   #[test]
   fn test_100() {
      const N: i32 = 100;

      let speech = number_to_speech(N);

      assert_eq!(speech, "one hundred");
   }

   #[test]
   fn test_87() {
      const N: i32 = 87;

      let speech = number_to_speech(N);

      assert_eq!(speech, "eighty seven");
   }

   #[test]
   fn test_19() {
      const N: i32 = 19;

      let speech = number_to_speech(N);

      assert_eq!(speech, "nineteen");
   }

   #[test]
   fn test_15() {
      const N: i32 = 15;

      let speech = number_to_speech(N);

      assert_eq!(speech, "fifteen");
   }

   #[test]
   fn test_59() {
      const N: i32 = 59;

      let speech = number_to_speech(N);

      assert_eq!(speech, "fifty nine");
   }

    #[test]
   fn test_111() {
      const N: i32 = 111;

      let speech = number_to_speech(N);

      assert_eq!(speech, "one hundred and eleven");
   }

   #[test]
   fn test_101() {
      const N: i32 = 101;

      let speech = number_to_speech(N);

      assert_eq!(speech, "one hundred and one");
   }

   #[test]
   fn test_923() {
      const N: i32 = 923;

      let speech = number_to_speech(N);

      assert_eq!(speech, "nine hundred and twenty three");
   }

    #[test]
   fn test_count_of_characters_between_1_and_5() {
      let count = count_characters_in_interval(1,5);

      assert_eq!(count, 19);
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);

   let count = count_characters_in_interval(1, 1000);

   writeln!(handle, "{}", count).ok();
}
