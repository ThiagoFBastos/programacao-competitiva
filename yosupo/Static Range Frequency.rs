#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, Error, ErrorKind, Write};
use std::rc::Rc;

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

struct Node {
   sum: i32,
   left: Option<Rc<Node>>,
   right: Option<Rc<Node>>
}

impl Node {

   fn new() -> Self {

      Self {
         sum: 0,
         left: None,
         right: None
      }
   }
}

struct SegTree {
   nodes: Vec<Option<Rc<Node>>>,
   len: usize
}

impl SegTree {

   fn new(len: usize) -> Self {

      if len == 0 {
         return Self {
            nodes: vec![],
            len
         };
      }

      Self {
         nodes: vec![Self::build(0, len - 1)],
         len
      }
   }

   fn build(lo: usize, hi: usize) -> Option<Rc<Node>> {
      let mut node = Node::new();

      if lo != hi {
         let mid = (lo + hi) / 2;
         node.left = Self::build(lo, mid);
         node.right = Self::build(mid + 1, hi);
      }

      return Some(Rc::new(node));
   }

   fn query(&self, node: &Option<Rc<Node>>, l: usize, r: usize, a: usize, b: usize) -> i32 {
      if r < a || l > b || l > r {
         return 0;
      } else if l >= a && r <= b {
         return node.as_ref().unwrap().sum;
      }

      let mid = (l + r) / 2;

      let p1 = self.query(&node.as_ref().unwrap().left, l, mid, a, b);
      let p2 = self.query(&node.as_ref().unwrap().right, mid + 1, r, a, b);

      return p1 + p2;
   }

   fn update(&mut self, previous: &Option<Rc<Node>>, l: usize, r: usize, pos: usize, k: i32) -> Option<Rc<Node>> {
      if pos > r || pos < l || l > r {
         return None;
      }

      let mut node = Node::new();

      node.sum = previous.as_ref().unwrap().sum + k;

      let mid = (l + r) / 2;

      if l != r {
         if pos <= mid {
            node.left = self.update(&previous.as_ref().unwrap().left, l, mid, pos, k);
            node.right = previous.as_ref().unwrap().right.clone();
         } else {
            node.left = previous.as_ref().unwrap().left.clone();
            node.right = self.update(&previous.as_ref().unwrap().right, mid + 1, r, pos, k);
         }
      }

      return Some(Rc::new(node));
   }

   fn answer(&self, a: usize, b: usize, p: usize) -> i32 {
      return self.query(&self.nodes[p], 0, self.len - 1, a, b);
   }

   fn new_node_update(&mut self, previous: usize, pos: usize, k: i32) {
      let previous = self.nodes[previous].clone();
      let node = self.update(&previous, 0, self.len - 1, pos, k);
      self.nodes.push(node);
   }
}

fn main() {
   let stdout = std::io::stdout();
   let mut handle = std::io::BufWriter::new(stdout);

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();

   if n == 0 {
      _ = sc.next::<String>();
   }

   let arr = (0..n).map(|_| sc.next::<i32>().unwrap()).collect::<Vec<_>>();

   let mut sorted_arr = arr.clone();

   sorted_arr.sort();
   sorted_arr.dedup();

   let mut st = SegTree::new(sorted_arr.len());

   for i in 0..n {
      let pos = sorted_arr.binary_search_by(|element| match element.cmp(&arr[i]) {
         std::cmp::Ordering::Equal => std::cmp::Ordering::Greater,
         ord => ord
      }).unwrap_err();

      st.new_node_update(i, pos, 1);
   }

   for _ in 0..q {
      let l = sc.next::<usize>().unwrap();
      let r = sc.next::<usize>().unwrap();
      let x = sc.next::<i32>().unwrap();

      let pos = sorted_arr.binary_search_by(|element| match element.cmp(&x) {
         std::cmp::Ordering::Equal => std::cmp::Ordering::Greater,
         ord => ord
      }).unwrap_err();

      if pos == sorted_arr.len() || sorted_arr[pos] != x {
         writeln!(handle, "0").ok();
         continue;
      }

      writeln!(handle, "{}", st.answer(pos, pos, r) - st.answer(pos, pos, l)).ok();
   }
}
