#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{HashMap, VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};

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
}

// Trait for initial value
pub trait SegTreeConstants {
    fn initial() -> Self;
}

#[derive(Clone)]
pub struct SegTree<T, OP>
where
    OP: Fn(T, T) -> T,
{
    data: Vec<T>,      // the segment tree data
    pub length: usize, // the number of elements
    op: OP,            // the binary operator
}

impl<T: SegTreeConstants + Copy, OP> SegTree<T, OP>
where
    OP: Fn(T, T) -> T,
{
    /**
     * Create a new instance of SegTree
     * @param values the initial array
     * @param op the binary operator to calculate the values
     */
    pub fn new(values: &[T], op: OP) -> Self {
        let n = values.len();
        let mut data = vec![T::initial(); 2 * n];

        data[n..(2 * n)].copy_from_slice(&values[..n]);

        for i in (1..n).rev() {
            data[i] = op(data[i << 1], data[(i << 1) | 1]);
        }

        Self {
            data,
            length: n,
            op,
        }
    }

    /**
     * Find the answer of query between l and r
     * @param l the leftmost position of the interval
     * @param r the rightmost position of the interval
     * @return the query answer of the values inside of the interval [l, r]
     */
    pub fn query(&self, mut l: usize, mut r: usize) -> T {
        let mut answer = T::initial();

        assert!(l <= r && r < self.length);

        l += self.length;
        r += self.length;

        while l <= r {
            if l & 1 == 1 {
                answer = (self.op)(answer, self.data[l]);
                l += 1;
            }

            if r & 1 == 0 {
                answer = (self.op)(answer, self.data[r]);
                r -= 1;
            }

            l >>= 1;
            r >>= 1;
        }

        answer
    }

    /**
     * Update a position to replacing the old value by the new one
     * @param k the position to change the value
     * @param value the value that will be replaced at position k
     */
    pub fn update(&mut self, mut k: usize, value: T) {
        assert!(k < self.length);

        k += self.length;

        self.data[k] = value;

        while k > 1 {
            k >>= 1;
            self.data[k] = (self.op)(self.data[k << 1], self.data[(k << 1) | 1]);
        }
    }
}

impl SegTreeConstants for i32 {
    fn initial() -> Self {
        0
    }
}

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    let n = sc.next::<usize>().unwrap();

    let buggies = (0..n).map(|_| sc.next::<i32>().unwrap()).collect::<Vec<_>>();

    let mut st = SegTree::new(&buggies, |a, b| a + b);

    loop {
        let opr = sc.next::<char>();

        if opr.is_err() {
            break;
        }

        let op = opr.unwrap();
        let i = sc.next::<usize>().unwrap() - 1;

        if op == 'a' {
            st.update(i, 0);
        } else {
            if i == 0 {
                writeln!(writer, "0").ok();
                continue;
            }

            let count = st.query(0, i - 1);

            writeln!(writer, "{}", count).ok();
        }
    }
}