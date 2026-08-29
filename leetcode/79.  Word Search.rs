impl Solution {
    pub fn exist(board: Vec<Vec<char>>, word: String) -> bool {
        let len = word.len();
        let n = board.len();
        let m = board[0].len();
        let characters = word.chars().collect::<Vec<_>>();

        fn backtracking(pos: usize, x: usize, y: usize, board: &[Vec<char>], word: &[char], busy: &mut [Vec<bool>]) -> bool {
            if pos == word.len() - 1 {
                return true;
            }

            let n = board.len();
            let m = board[0].len();
            let delta = [(0, 1), (0, -1), (1, 0), (-1, 0)];

            for (dx, dy) in delta {
                let x_dest = x as i32 + dx;
                let y_dest = y as i32 + dy;

                if x_dest < 0 || y_dest < 0 || x_dest >= n as i32 || y_dest >= m as i32 {
                    continue;
                }

                let n_x = x_dest as usize;
                let n_y = y_dest as usize;

                if busy[n_x][n_y] {
                    continue;
                }

                busy[n_x][n_y] = true;

                if word[pos + 1] == board[n_x][n_y] && backtracking(pos + 1, n_x, n_y, board, word, busy) {
                    return true;
                }

                busy[n_x][n_y] = false;
            }

            false
        }

        for i in 0..n {
            for j in 0..m {
                let mut busy = vec![vec![false; m]; n];

                busy[i][j] = true;
                if characters[0] == board[i][j] && backtracking(0, i, j, &board, &characters, &mut busy) {
                    return true;
                }
            }
        }

        false
    }
}