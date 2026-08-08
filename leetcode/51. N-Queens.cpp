#include <bitset>

class Solution {
	bitset<30> row, main_diagon, sec_diagon;
	vector<string> grid;
	vector<vector<string>> sols;
	int n;
		
	bool canPlace(int r, int c) {
		return !(row[r] || sec_diagon[r + c] || main_diagon[9 + r - c]);
	}
	
	void backtracking(int c) {
		if(c == n) {
			sols.emplace_back(grid);
			return;
		}
		for(int r = 0; r < n; ++r) {
			if(!canPlace(r, c)) continue;
			row[r] = sec_diagon[r + c] = main_diagon[9 + r - c] = 1;
			grid[r][c] = 'Q';
			backtracking(c + 1);
			grid[r][c] = '.';
			row[r] = sec_diagon[r + c] = main_diagon[9 + r - c] = 0;
		}
	}
	
public:
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        grid = vector<string>(n, string(n, '.'));
        backtracking(0);
        return sols;
    }
};