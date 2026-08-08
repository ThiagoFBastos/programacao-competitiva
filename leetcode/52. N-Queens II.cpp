#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

#include <bitset>

class Solution {
	bitset<30> row, main_diagon, sec_diagon;
	int n, cnt = 0;
		
	bool canPlace(int r, int c) {
		return !(row[r] || sec_diagon[r + c] || main_diagon[9 + r - c]);
	}
	
	void backtracking(int c) {
		if(c == n) {
			++cnt;
			return;
		}
		for(int r = 0; r < n; ++r) {
			if(!canPlace(r, c)) continue;
			row[r] = sec_diagon[r + c] = main_diagon[9 + r - c] = 1;
			backtracking(c + 1);
			row[r] = sec_diagon[r + c] = main_diagon[9 + r - c] = 0;
		}
	}
	
public:
    int totalNQueens(int n) {
        this->n = n;
        backtracking(0);
        return cnt;
    }
};