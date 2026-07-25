#![allow(dead_code)]
use std::{
    io::{self, Read, Write},
    writeln,
};

struct Scanner {
    buffer: Vec<u8>,
    index: usize,
}

impl Scanner {
    fn new() -> Self {
        let mut input = Vec::new();

        io::stdin().read_to_end(&mut input).unwrap();

        Self {
            buffer: input,
            index: 0,
        }
    }

    fn has_next(&mut self) -> bool {
        while self.index < self.buffer.len() && self.buffer[self.index].is_ascii_whitespace() {
            self.index += 1;
        }

        self.index < self.buffer.len()
    }

    fn next<T: std::str::FromStr>(&mut self) -> T {
        if !self.has_next() {
            panic!("End Of File");
        }

        let start = self.index;

        while self.index < self.buffer.len() && !self.buffer[self.index].is_ascii_whitespace() {
            self.index += 1;
        }

        std::str::from_utf8(&self.buffer[start..self.index])
            .unwrap()
            .parse::<T>()
            .ok()
            .unwrap()
    }
}

fn gcd(mut a: i32, mut b: i32) -> i32 {
    while a != 0 {
        let temp = a;
        a = b % a;
        b = temp;
    }
    b
}

fn factors(mut n: i32) -> Vec<i32> {
    let mut primes = Vec::new();
    let mut p = 2;

    while p * p <= n {
        if n % p == 0 {
            primes.push(p);

            while n % p == 0 {
                n /= p;
            }
        }

        p += 1;
    }

    if n != 1 {
        primes.push(n);
    }

    primes
}

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    let a = sc.next::<i32>();
    let b = sc.next::<i32>();
    let mut c = gcd(a, b);
    let mut l2 = 1;

    let primes = factors(c);

    for p in primes {
        let mut odd = false;
        let prime = p as i64;

        while c % p == 0 {
            c /= p;
            odd = !odd;
            l2 *= prime;
        }

        if odd {
            l2 *= prime;
        }
    }

    let l = (l2 as f64).sqrt() as i64;

    writeln!(writer, "{}", l).ok();
}
