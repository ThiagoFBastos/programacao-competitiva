#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::VecDeque;
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};

struct Scanner {
    buffer: VecDeque<String>,
    reader: io::BufReader<io::Stdin>,
}

impl Scanner {
    fn new() -> Self {
        Self {
            buffer: VecDeque::new(),
            reader: io::BufReader::new(io::stdin()),
        }
    }

    fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
        if self.buffer.is_empty() {
            let mut input = String::new();

            match self.reader.read_line(&mut input) {
                Ok(0) => {
                    return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
                }
                Ok(_) => {}
                Err(e) => {
                    return Err(e);
                }
            }

            self.buffer = input.split_whitespace().map(|x| x.to_string()).collect();

            if self.buffer.is_empty() {
                self.buffer.push_back("".to_string());
            }
        }

        let front = self.buffer.pop_front().unwrap();

        Ok(front.parse::<T>().ok().unwrap())
    }
}

fn main() {
    let mut writer = io::BufWriter::new(io::stdout());

    let mut sc = Scanner::new();

    const KEYS: usize = 16;
    const JEWELS: usize = 32;

    let n = sc.next::<usize>().unwrap();
    let m = sc.next::<usize>().unwrap();

    let grid = (0..n)
        .map(|_| sc.next::<String>().unwrap().chars().collect())
        .collect::<Vec<Vec<_>>>();

    let mut dist = vec![vec![[[None; JEWELS]; KEYS]; m]; n];
    let mut queue = VecDeque::new();
    let delta = [(1, 0), (-1, 0), (0, 1), (0, -1)];

    let to_state = |c: char, mask1: usize, mask2: usize| {
        let jewels = ['p', 't', 'm', 'e', 'r'];
        let keys = ['a', 'b', 'c', 'd'];
        let basic_places = ['.', 'T'];
        let doors = ['A', 'B', 'C', 'D'];

        if basic_places.contains(&c) {
            return Some((mask1, mask2));
        } else if let Some(it) = jewels.iter().enumerate().find(|x| *x.1 == c) {
            let pos = it.0;
            return Some((mask1, mask2 | (1 << pos)));
        } else if let Some(it) = keys.iter().enumerate().find(|x| *x.1 == c) {
            let pos = it.0;
            return Some((mask1 | (1 << pos), mask2));
        } else if let Some(it) = doors.iter().enumerate().find(|x| *x.1 == c) {
            let pos = it.0;

            if mask1 & (1 << pos) != 0 {
                return Some((mask1, mask2));
            }
        }

        None
    };

    let mut starting = None;

    'a: for (x, row) in grid.iter().enumerate() {
        for (y, col) in row.iter().enumerate() {
            if *col == 'T' {
                starting = Some((x, y));
                break 'a;
            }
        }
    }

    assert!(starting.is_some());

    let (x0, y0) = starting.unwrap();

    queue.push_back((x0, y0, 0, 0));
    dist[x0][y0][0][0] = Some(0);

    let mut answer = None;

    while let Some((x, y, mask1, mask2)) = queue.pop_front() {
        let d = dist[x][y][mask1][mask2].unwrap();

        if mask2 == JEWELS - 1 {
            answer = Some(d);
            break;
        }

        for &(dx, dy) in &delta {
            let xto = x as i32 + dx;
            let yto = y as i32 + dy;

            if xto < 0 || yto < 0 || xto >= n as i32 || yto >= m as i32 {
                continue;
            }

            let x_to = xto as usize;
            let y_to = yto as usize;

            if let Some((m1, m2)) = to_state(grid[x_to][y_to], mask1, mask2) {
                if dist[x_to][y_to][m1][m2].is_some() {
                    continue;
                }

                dist[x_to][y_to][m1][m2] = Some(d + 1);
                queue.push_back((x_to, y_to, m1, m2));
            }
        }
    }

    if let Some(d) = answer {
        writeln!(writer, "{}", d).ok();
    } else {
        writeln!(writer, "Gamora").ok();
    }
}
