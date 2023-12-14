#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m, **p, C[1000], L[1000];
	char **grid;
	scanf("%d%d", &n, &m);
	grid = new char*[n];
	p = new int*[n];
	for(int k = 0; k < n; ++k) {
		grid[k] = new char[m];
		p[k] = new int[m + 1];
		getchar();
		for(int i = 0; i < m; ++i)
			grid[k][i] = getchar();	
	}
	for(int k = 0; k < n; ++k) {
		p[k][m] = 0;
		for(int i = m - 1; i >= 0; --i) {
			if(grid[k][i] == '.')
				p[k][i] = 1 + p[k][i + 1];
			else
				p[k][i] = 0;
		}
	}
	int area = 0;
	for(int i = 0; i < m; ++i) {
		stack<int> S;
		for(int k = 0; k < n; ++k) {
			C[k] = p[k][i];
			while(!S.empty() && C[S.top()] >= p[k][i]) S.pop();
			if(S.empty()) L[k] = 0;
			else L[k] = S.top();
			S.push(k); 		
		}
		while(!S.empty()) S.pop();
		for(int k = n - 1; k >= 0; --k) {
			int r;
			while(!S.empty() && C[S.top()] >= p[k][i]) S.pop();
			if(S.empty()) r = n - 1;
			else r = S.top();
			S.push(k);
			if(C[L[k]] < C[k]) ++L[k];
			if(C[r] < C[k]) --r;
			area = max(area, C[k] * (r - L[k] + 1));
		}
	}
	printf("%d\n", area);
	return 0;
}
