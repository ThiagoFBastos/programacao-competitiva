#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
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
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

fn coins_combinations(coins: &mut [usize], target: usize) -> i32 {
   let n = coins.len();

   coins.sort();

   let mut dp = vec![0; target + 1];
   const MOD: i32 = 1_000_000_007;

   dp[0] = 1;

   for i in coins[0]..=target {
      let mut sum = 0;

      for j in 0..n {
         if coins[j] > i {
            break;
         }

         sum += dp[i - coins[j]];

         if sum >= MOD {
            sum -= MOD;
         }
      }

      dp[i] = sum;
   }

   dp[target]
}

#[cfg(test)]
mod unit_tests {
   use super::*;

   #[test]
   fn test_sample_case() {
      let target = 9;
      let mut coins = vec![2, 3, 5];

      let result = coins_combinations(&mut coins, target);

      assert_eq!(result, 8);
   }

   #[test]
   fn test_sample_case_shuffled() {
      let target = 9;
      let mut coins = vec![5, 2, 3];

      let result = coins_combinations(&mut coins, target);

      assert_eq!(result, 8);
   }

   #[test]
   fn test_fibonnaci_10() {
      let target = 10;
      let mut coins = vec![1, 2];

      let result = coins_combinations(&mut coins, target);

      assert_eq!(result, 89);
   }

   #[test]
   fn test_fibonnaci_11() {
      let target = 11;
      let mut coins = vec![2, 1];

      let result = coins_combinations(&mut coins, target);

      assert_eq!(result, 144);
   }

}
fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().ok().unwrap();
   let target = sc.next::<usize>().ok().unwrap();

   let mut coins = (0..n).map(|_| sc.next::<usize>().ok().unwrap()).collect::<Vec<_>>();

   let result = coins_combinations(&mut coins, target);

   writeln!(handle, "{result}").ok();
 }