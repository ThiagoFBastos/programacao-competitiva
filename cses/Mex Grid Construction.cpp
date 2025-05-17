#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 1e2 + 5;
 
int grid[N][N];
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n;
 
	cin >> n;
 
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			bitset<N> mex;
 
			for(int k = 0; k < i; ++k) mex[grid[k][j]] = 1;
			for(int k = 0; k < j; ++k) mex[grid[i][k]] = 1;
 
			int& val = grid[i][j];
 
			while(mex[val]) ++val;
 
			cout << val << ' ';
		}
 
		cout << '\n';
	}
 
	return 0;
}
