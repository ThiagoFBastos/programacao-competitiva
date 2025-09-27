#![allow(unused_imports)]
use std::collections::{VecDeque};
use std::hash::Hash;
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

fn reorder(s: &String) -> Option<String> {

   let str = s.chars().collect::<Vec<_>>();
   
   let mut frequency = [0; 26];

   let mut max_frequency = 0;

   for ch in str.iter() {
      let pos = *ch as usize - 'A' as usize;
      frequency[pos] += 1;
   }

   for count in frequency.iter() {
      max_frequency = max_frequency.max(*count);
   }

   if 2 * max_frequency - 1 > str.len() {
      return None;
   }

   let mut k = 0;
   let mut i = 0;
   let mut letters = Vec::new();

   'outer: while i < 26 {

      k = k.max(i + 1);

      loop {
         if frequency[i as usize] == 0 {
            break;
         }

         frequency[i as usize] -= 1;

         while k < 26 && frequency[k as usize] == 0 {
            k += 1;
         }

         letters.push(i);

         if frequency[i as usize] > 0 {

            if k == 26 {
               break 'outer;
            }

            frequency[k as usize] -= 1;
            letters.push(k);
         }
      }

      i += 1;
   }

   if i < 26 {
      let mut rearranged = Vec::new();

      k = letters.len() as i32 - 1;
      
      while k >= 0 {

         if frequency[i as usize] > 0 {
            if rearranged.is_empty() {
               rearranged.push(letters[k as usize]);
               k -= 1;
            } else if *rearranged.last().unwrap() != i && letters[k as usize] != i {
               rearranged.push(i);
               frequency[i as usize] -= 1;
            } else {
               rearranged.push(letters[k as usize]);
               k -= 1;
            }
         } else {
            rearranged.push(letters[k as usize]);
            k -= 1;
         }
      }

      if frequency[i as usize] > 0 {
         rearranged.push(i);
      }

      rearranged.reverse();

      k = 0;

      while k < rearranged.len() as i32 && rearranged[k as usize] != i {
         k += 1;
      } 

      frequency.fill(0);

      for j in (k + 1) as usize..rearranged.len() {
         if rearranged[j] != i {
            frequency[rearranged[j] as usize] += 1;
         }
      }

      i = 0;

      for j in ((k + 1) as usize..rearranged.len()).step_by(2) {
         while i < 26 && frequency[i as usize] == 0 {
            i += 1;
         }

         rearranged[j] = i;

         frequency[i as usize] -= 1;
      }
      
      letters = rearranged;
   }
   
   let output = letters.iter().map(|pos| (*pos as u8 + 'A' as u8) as char).collect::<String>();

   return Some(output);
}

#[cfg(test)]
mod tests {
   use super::*;

   #[test]
   fn test_sample_test() {
      let input = String::from("HATTIVATTI");
      let expected = Some(String::from("AHATITITVT"));

      let result = reorder(&input);

      assert_eq!(result, expected);
   }

   #[test]
   fn test_simple_no_solution_case() {
      let input = String::from("AA");
      let expected = None;

      let result = reorder(&input);

      assert_eq!(result, expected);
   }

   #[test]
   fn test_simple_case() {
      let input = String::from("CBA");
      let expected = Some(String::from("ABC"));

      let result = reorder(&input);

      assert_eq!(result, expected);
   }
}
fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let s = sc.next::<String>().ok().unwrap();

   if let Some(output) = reorder(&s) {
      writeln!(handle, "{}", output).ok();
   } else {
      writeln!(handle, "-1").ok();
   }
 }