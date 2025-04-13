#include <bits/stdc++.h>
using namespace std; 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, r, c;
	char M[100][101];
	while(true) {
		cin >> n >> m >> r >> c;
		if(n == 0 && m == 0 && r == 0 && c == 0)
			break;
		for(int k = 0; k < n; ++k)
			cin >> M[k];
		int x = 0, y = 0, op = 0;
		int R = n, C = m;
		while(n >= r && m >= c) {
			if(M[x][y] == '1' && x + r < n && y + c < m) {
				++op;
				for(int k = x; k < x + r; ++k)
					for(int i = y; i < y + c; ++i)
						M[k][i] ^= 1;
			}
			if(M[n - 1][y] == '1' && n - r >= x && y + c < m) {
				++op;
				for(int k = n - r; k < n; ++k)
					for(int i = y; i < y + c; ++i)
						M[k][i] ^= 1;
			}
			if(M[x][m - 1] == '1' && x + r < n && m - c >= y) {
				++op;
				for(int k = x; k < x + r; ++k)
					for(int i = m - c; i < m; ++i)
						M[k][i] ^= 1;
			}
			if(M[n - 1][m - 1] == '1' && n - r >= x && m - c >= y) {
				++op;
				for(int k = n - r; k < n; ++k)
					for(int i = m - c; i < m; ++i)
						M[k][i] ^= 1;
			}
			for(int i = y; i < m; ++i) {
				if(M[x][i] == '1' && x + r < n && i + c < m) {
					++op;
					for(int k = x; k < x + r; ++k)
						for(int j = i; j < i + c; ++j)
							M[k][j] ^= 1;
				}
			}
			for(int i = y; i < m; ++i) {
				if(M[n - 1][i] == '1' && n - r >= x && i + c < m) {
					++op;
					for(int k = n - r; k < n; ++k)
						for(int j = i; j < i + c; ++j)
							M[k][j] ^= 1;
				}
			}
			for(int i = x; i < n; ++i) {
				if(M[i][y] == '1' && i + r < n && y + c < m) {
					++op;
					for(int k = i; k < i + r; ++k)
						for(int j = y; j < y + c; ++j)
							M[k][j] ^= 1;
				}
			}
			for(int i = x; i < n; ++i) {
				if(M[i][m - 1] == '1' && i + r < n && m - c >= y) {
					++op;
					for(int k = i; k < i + r; ++k)
						for(int j = m - c; j < m; ++j)
							M[k][j] ^= 1;
				}
			}
			--n, --m, ++x, ++y;
		}
		bool ok = true;
		for(int k = 0; k < R; ++k) {
			for(int i = 0; i < C; ++i) {
				if(M[k][i] != '0') {
					ok = false;
					i = m;
					break;
				}
			}
		}
		if(ok) cout << op << '\n';
		else cout << -1 << '\n';
	}
	return 0;
}