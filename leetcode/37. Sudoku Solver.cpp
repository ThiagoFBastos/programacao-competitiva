#include <bitset>

class Solution {
    bitset<9> row[9], col[9], grid[3][3];
    int g[9][9];
    
    bool backtracking(int k) {
        if(k == 81) return true;
        
        int x = k / 9, y = k % 9;
        
        if(g[x][y] >= 0) return backtracking(k + 1);
        
        auto S = (row[x] & col[y]) & grid[x / 3][y / 3];
        
        for(int i = 0; i < 9; ++i) {
            if(!S[i]) continue;
            row[x][i] = col[y][i] = grid[x / 3][y / 3][i] = 0;
            g[x][y] = i;
            if(backtracking(k + 1)) return true;
            g[x][y] = -1;
            row[x][i] = col[y][i] = grid[x / 3][y / 3][i] = 1;
        }
        
        return false;
    }
    
public:
    void solveSudoku(vector<vector<char>>& board) {
        for(int i = 0; i < 9; ++i) {
            row[i].set();
            col[i].set();
            grid[i / 3][i % 3].set();
            for(int j = 0; j < 9; ++j) g[i][j] = -1;
        }
        
        for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                char ch = board[i][j];
                if(ch == '.') continue;
                g[i][j] = ch - '1';
				row[i][ch - '1'] = col[j][ch - '1'] = grid[i / 3][j / 3][ch - '1'] = 0;
            }
        }
        
        backtracking(0);
        
        for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j)
            board[i][j] = g[i][j] + '1';
    }
};