#![allow(dead_code)]
use std::{
    collections::VecDeque,
    io::{self, Read, Write},
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

    let delta = [(0, 1), (0, -1), (1, 0), (-1, 0)];

    let r = sc.next::<usize>();
    let c = sc.next::<usize>();

    let grid = (0..r)
        .map(|_| (0..c).map(|_| sc.next::<char>()).collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let mut vis = vec![vec![false; c]; r];
    let mut queue = VecDeque::new();

    let mut max_connected_component = 0;

    for (i, row) in grid.iter().enumerate() {
        for (j, &element) in row.iter().enumerate() {
            if vis[i][j] || element != 'C' {
                continue;
            }

            let mut count = 0;

            vis[i][j] = true;
            queue.push_back((i, j));

            while let Some((x, y)) = queue.pop_front() {
                count += 1;

                for (dx, dy) in &delta {
                    let dest_x = x as i32 + dx;
                    let dest_y = y as i32 + dy;

                    if dest_x < 0 || dest_y < 0 || dest_x >= r as i32 || dest_y >= c as i32 {
                        continue;
                    }

                    let nx = dest_x as usize;
                    let ny = dest_y as usize;

                    if vis[nx][ny] || grid[nx][ny] != 'C' {
                        continue;
                    }

                    vis[nx][ny] = true;
                    queue.push_back((nx, ny));
                }
            }

            max_connected_component = max_connected_component.max(count);
        }
    }

    writeln!(writer, "{}", max_connected_component).ok();
}
