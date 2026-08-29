use std::collections::VecDeque;

impl Solution {
    pub fn solve(board: &mut Vec<Vec<char>>) {
        let r = board.len();
        let c = board[0].len();

        let mut vis = vec![vec![false; c]; r];
        let delta = [(0, 1), (0, -1), (1, 0), (-1, 0)];

        for x in 0..r {
            for y in 0..c {
                if vis[x][y] || board[x][y] != 'O' {
                    continue;
                }

                let mut queue = VecDeque::new();
                let mut locations = Vec::new();
                let mut is_outside = false;

                vis[x][y] = true;
                queue.push_back((x, y));

                while let Some((x, y)) = queue.pop_front() {

                    locations.push((x, y));

                    for &(dx, dy) in &delta {
                        let dest_x = x as i32 + dx;
                        let dest_y = y as i32 + dy;

                        if dest_x < 0 || dest_y < 0 || dest_x >= r as i32 || dest_y >= c as i32 {
                            is_outside = true;
                        } else {
                            let nx = dest_x as usize;
                            let ny = dest_y as usize;

                            if !vis[nx][ny] && board[nx][ny] == 'O' {
                                vis[nx][ny] = true;
                                queue.push_back((nx, ny));
                            }
                        }
                    }
                }

                if !is_outside {
                    for (x, y) in locations {
                        board[x][y] = 'X';
                    }
                }
            }
        }
    }
}