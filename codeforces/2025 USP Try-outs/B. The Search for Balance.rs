#![allow(unused_imports)]
#![allow(dead_code)]
use std::cmp::Ordering;
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

      if self.buffer.is_empty() {
         self.buffer.push_back("".to_string());
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
}

struct FenwickTree {
   ft: Vec<i32>,
   len: usize
}

impl FenwickTree {

   fn new(len: usize) -> Self {

      Self {
         ft: vec![0; len + 1],
         len
      }
   }

   fn query(&self, mut k: i32) -> i32 {
      let mut result = 0;

      while k > 0 {
         result += self.ft[k as usize];
         k -= k & -k;
      }

      result
   }

   fn update(&mut self, mut k: i32, value: i32) {
      while k <= self.len as i32 {
         self.ft[k as usize] += value;
         k += k & -k;
      }
   }
}

struct OrderedSet {
   ft: FenwickTree,
   keys: Vec<i64>
}

impl OrderedSet {

   fn new(mut keys: Vec<i64>) -> Self {

      keys.push(i64::MIN);
      keys.push(i64::MAX);
      keys.sort();

      Self {
         ft: FenwickTree::new(keys.len()),
         keys
      }
   }

   fn get_position(&self, value: i64) -> usize {

      self.keys.binary_search_by(|element| match element.cmp(&value) {
         Ordering::Equal => Ordering::Greater,
         ord => ord
      }).unwrap_err()
   }

   fn insert(&mut self, value: i64) {
      let pos = self.get_position(value);

      assert!(pos < self.keys.len() && self.keys[pos] == value);

      self.ft.update(pos as i32 + 1, 1);
   }

   fn order_of_key(&self, value: i64) -> i32 {
      let pos =  self.keys.binary_search_by(|element| match element.cmp(&value) {
         Ordering::Equal => Ordering::Greater,
         ord => ord
      }).unwrap_err() - 1;

      self.ft.query(pos as i32 + 1)
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);
 
   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();

   let mut power_up = Vec::with_capacity(n);

   for _ in 0..n {
      let a = sc.next::<i64>().unwrap();
      let d = sc.next::<i64>().unwrap();

      power_up.push((a, d));
   }

   let a1 = sc.next::<i64>().unwrap();
   let d1 = sc.next::<i64>().unwrap();
   let a2 = sc.next::<i64>().unwrap();
   let d2 = sc.next::<i64>().unwrap();

   if n <= 10 {
      let mut count = 0;

      for i in 0..(1 << n) {
         let mut attack = 0;
         let mut defense = 0;

         for j in 0..n {
            if (i >> j) & 1 == 1 {
               attack += power_up[j].0;
               defense += power_up[j].1;
            }
         }

         if attack >= a1 && attack <= a2 && defense >= d1 && defense <= d2 {
            count += 1;
         } 
      }

      writeln!(handle, "{}", count).ok();
      return;
   }

   let mid = n / 2;

   let first_power_up = &power_up[0..mid];
   let second_power_up = &power_up[mid..n];

   let get_power_up_combinations = |power_up: &[(i64, i64)]| {
      let n = power_up.len();
      let mut combinations = Vec::with_capacity(1 << n);

      for i in 0..(1 << n) {
          let mut attack = 0;
         let mut defense = 0;

         for j in 0..n {
            if (i >> j) & 1 == 1 {
               attack += power_up[j].0;
               defense += power_up[j].1;
            }
         }

         combinations.push((attack, defense));
      }

      combinations
   };

   let first_power_up_combinations = get_power_up_combinations(&first_power_up);
   let second_power_up_combinations = get_power_up_combinations(&second_power_up);

   let mut answer = 0_i64;

   let mut sweep = Vec::with_capacity(2 * first_power_up_combinations.len() + second_power_up_combinations.len());

   for &(attack, defense) in first_power_up_combinations.iter() {
      sweep.push((a1 - attack, 0, d1 - defense, d2 - defense));
      sweep.push((a2 - attack, 2, d2 - defense, d1 - defense));
   }

   for &(attack, defense) in second_power_up_combinations.iter() {
      sweep.push((attack, 1, defense, 0)); 
   }

   let keys = second_power_up_combinations.iter().map(|element| element.1).collect::<Vec<i64>>();

   let mut os = OrderedSet::new(keys);

   sweep.sort();

   for &(_, case, defense, defense2) in sweep.iter() {
      
      if case == 0 {
         answer -= os.order_of_key(defense2 + 1) as i64;
         answer += os.order_of_key(defense) as i64;
      } else if case == 1 {
         os.insert(defense);
      } else {
         answer += os.order_of_key(defense + 1) as i64;
         answer -= os.order_of_key(defense2) as i64;
      }
   }

   writeln!(handle, "{}", answer).ok();
 }
