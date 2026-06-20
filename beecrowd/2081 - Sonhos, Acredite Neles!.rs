#![allow(dead_code)]
use std::collections::VecDeque;
use std::io::{self, Read, Write};

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

    fn next<T: std::str::FromStr>(&mut self) -> T {
        while self.index < self.buffer.len() && self.buffer[self.index].is_ascii_whitespace() {
            self.index += 1;
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
    let mut writer = io::BufWriter::with_capacity(8 << 20, io::stdout());

    let mut sc = Scanner::new();

    let t = sc.next::<usize>();

    const N: usize = 50 * 50 * 50 * 50 + 5;

    let mut distance = vec![None; N];

    let delta = [(1, 0), (-1, 0), (0, 1), (0, -1)];

    for _ in 0..t {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();

        for val in distance.iter_mut().take(n * m * n * m) {
            *val = None;
        }

        let position = |x0: usize, y0: usize, x1: usize, y1: usize| {
            let i = x0 * m + y0;
            let j = x1 * m + y1;

            i * n * m + j
        };

        let is_valid_position = |x: i32, y: i32| x >= 0 && x < n as i32 && y >= 0 && y < m as i32;

        let map1 = (0..n)
            .map(|_| sc.next::<String>())
            .map(|s| s.chars().collect())
            .collect::<Vec<Vec<_>>>();

        let map2 = (0..n)
            .map(|_| sc.next::<String>())
            .map(|s| s.chars().collect())
            .collect::<Vec<Vec<_>>>();

        let mut starting_robot_1 = None;
        let mut starting_robot_2 = None;

        'a: for (x, row) in map1.iter().enumerate() {
            for (y, &c) in row.iter().enumerate() {
                if c == 'R' {
                    starting_robot_1 = Some((x, y));
                    break 'a;
                }
            }
        }

        'b: for (x, row) in map2.iter().enumerate() {
            for (y, &c) in row.iter().enumerate() {
                if c == 'R' {
                    starting_robot_2 = Some((x, y));
                    break 'b;
                }
            }
        }

        assert!(starting_robot_1.is_some() && starting_robot_2.is_some());

        let (x0, y0) = starting_robot_1.unwrap();
        let (x1, y1) = starting_robot_2.unwrap();

        let mut queue = VecDeque::new();
        let mut answer = None;

        queue.push_back((x0, y0, x1, y1));
        distance[position(x0, y0, x1, y1)] = Some(0);

        while let Some((x0, y0, x1, y1)) = queue.pop_front() {
            let pos = position(x0, y0, x1, y1);
            let dist = distance[pos].unwrap();

            if map1[x0][y0] == 'F' && map2[x1][y1] == 'F' {
                answer = Some(dist);
                break;
            }

            for &(dx, dy) in &delta {
                let x0_to = x0 as i32 + dx;
                let y0_to = y0 as i32 + dy;
                let x1_to = x1 as i32 + dx;
                let y1_to = y1 as i32 + dy;

                if !is_valid_position(x0_to, y0_to) || !is_valid_position(x1_to, y1_to) {
                    continue;
                }

                let mut x0_to = x0_to as usize;
                let mut y0_to = y0_to as usize;
                let mut x1_to = x1_to as usize;
                let mut y1_to = y1_to as usize;

                if map1[x0_to][y0_to] == 'B' || map2[x1_to][y1_to] == 'B' {
                    continue;
                }

                if map1[x0_to][y0_to] == '#' {
                    x0_to = x0;
                    y0_to = y0;
                }

                if map2[x1_to][y1_to] == '#' {
                    x1_to = x1;
                    y1_to = y1;
                }

                let pos_to = position(x0_to, y0_to, x1_to, y1_to);

                if distance[pos_to].is_some() {
                    continue;
                }

                distance[pos_to] = Some(1 + dist);
                queue.push_back((x0_to, y0_to, x1_to, y1_to));
            }
        }

        if let Some(dist) = answer {
            writeln!(writer, "{}", dist).ok();
        } else {
            writeln!(writer, "impossivel").ok();
        }
    }
}
