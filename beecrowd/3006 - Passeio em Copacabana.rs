#![allow(dead_code)]
use std::{
    collections::VecDeque,
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

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    let t = sc.next::<usize>();

    let store = ['C', 'F'];
    let delta = [-1, 1];

    for _ in 0..t {
        let avenue = sc.next::<String>();

        let n = avenue.len();

        let mut dist = vec![[-1; 4]; n];
        let mut queue = VecDeque::new();

        let chars = avenue.chars().collect::<Vec<_>>();

        for (i, c) in chars.iter().enumerate() {
            if *c == 'R' {
                dist[i][0] = 0;
                queue.push_back((i, 0));
            }
        }

        let mut answer = None;

        while let Some((x, mask)) = queue.pop_front() {
            if mask == 3 {
                answer = Some(dist[x][mask]);
                break;
            }

            for &dx in &delta {
                let dest = x as i32 + dx;

                if dest < 0 || dest >= n as i32 {
                    continue;
                }

                let mut new_mask = mask;

                for (i, &c) in store.iter().enumerate() {
                    if chars[dest as usize] == c {
                        new_mask |= 1 << i;
                        break;
                    }
                }

                if dist[dest as usize][new_mask] != -1 {
                    continue;
                }

                dist[dest as usize][new_mask] = 1 + dist[x][mask];
                queue.push_back((dest as usize, new_mask));
            }
        }

        assert!(answer.is_some());

        writeln!(writer, "{}", answer.unwrap()).ok();
    }
}
