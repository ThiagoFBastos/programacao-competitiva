#include "quality.h"
#include<cstdio>
const int N = 3e3 + 10;
 
int ps[N][N];
 
int query(int x0, int y0, int x1, int y1) {
	return ps[x1][y1] - ps[x1][y0-1] - ps[x0-1][y1] + ps[x0-1][y0-1];
}
 
int rectangle(int R, int C, int H, int W, int Q[3001][3001]) {
	int lo = 1, hi = R * C;
 
	while(lo < hi) {
		int m = (lo + hi) / 2, best = -R * C;
		
		for(int i = 1; i <= R; ++i) {
			for(int j = 1; j <= C; ++j) {
				ps[i][j] = Q[i-1][j-1] > m ? -1 : 1;
				ps[i][j] += ps[i - 1][j];
				ps[i][j] += ps[i][j - 1];
				ps[i][j] -= ps[i - 1][j - 1];
			}
		}
 
		for(int i = 1; i <= R - H + 1; ++i) {
			for(int j = 1; j <= C - W + 1; ++j) {
				int s = query(i, j, i + H - 1, j + W - 1);
				if(best < s) best = s;
			}
		}
		
		if(best >= 0) hi = m;
		else lo = m + 1;
	}
 
	return hi;
}
