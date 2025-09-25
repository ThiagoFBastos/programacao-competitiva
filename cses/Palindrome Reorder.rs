#![allow(unused_imports)]
use std::collections::{VecDeque, HashMap};
use std::io::{self, Error, ErrorKind, Write};
use std::str::FromStr;

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
               return Err(Error::new(ErrorKind::UnexpectedEof, "End Of Line"));
            } Ok(_) => {
               
            } Err(e) => {
               return Err(e);
            }
         }
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn rearrange_to_palindrome(text: &String) -> String {
   let str = text.chars().collect::<Vec<char>>();

   let mut frequency = HashMap::new();
   let mut odd = 0;

   let mut answer = vec!['\0'; str.len()];
   let mut lo = 0;
   let mut hi = str.len() - 1;

   for &ch in str.iter() {
      let count = frequency.get(&ch).unwrap_or(&0);
      frequency.insert(ch, *count + 1);
   }

   for (_, count) in frequency.iter() {
      if *count % 2 == 1 {
         odd += 1;
      }
   }

   if str.len() % 2 == 1 {

      if odd == 1 {
         for (ch, count) in frequency.iter() {
            let n = *count / 2;

            for _ in 0..n {
               answer[lo] = *ch;
               answer[hi] = *ch;
               lo += 1;
               hi -= 1;
            }
         }

         for (ch, count) in frequency.iter() {

            if *count % 2 == 1 {
               answer[lo] = *ch;
               break;
            }
         }

         let output = answer.iter().collect::<String>();

         return output;
      } else {
        return String::from("NO SOLUTION");
      }
   } else if odd > 0 {
      return String::from("NO SOLUTION");
   } else {
      for (ch, count) in frequency.iter() {
         let n = *count / 2;

         for _ in 0..n {
            answer[lo] = *ch;
            answer[hi] = *ch;
            lo += 1;
            hi -= 1;
         }
      }

      let output = answer.iter().collect::<String>();

      return output;
   }
}


#[cfg(test)]
mod tests {
   use super::*;

   fn is_palindrome(text: &String) -> bool {
      let mut chars = text.chars().collect::<Vec<char>>();
      chars.reverse();
      return *text == chars.iter().collect::<String>();
   }

   #[test]
   fn check_odd_string() {
      let text = String::from("BAACDCD");

      let palindrome = rearrange_to_palindrome(&text);

      assert!(is_palindrome(&palindrome));
   }

   #[test]
   fn check_even_string() {
      let text = String::from("XXYY");

      let palindrome = rearrange_to_palindrome(&text);

      assert!(is_palindrome(&palindrome));
   }

   #[test]
   fn check_odd_no_solution() {
      let text = String::from("BAACDC");
      let expected = String::from("NO SOLUTION");

      let result = rearrange_to_palindrome(&text);

      assert_eq!(result, expected);
   }

   #[test]
   fn check_even_no_solution() {
      let text = String::from("AB");
      let expected = String::from("NO SOLUTION");

      let result = rearrange_to_palindrome(&text);

      assert_eq!(result, expected);
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let str = sc.next::<String>().ok().unwrap();

   writeln!(handle, "{}", rearrange_to_palindrome(&str)).ok();
}