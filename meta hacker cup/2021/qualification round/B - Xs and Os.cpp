#include "bits/stdc++.h"

using namespace std;

void solve() {
	int n;
	
	cin >> n;
	
	vector<int> Ocols(n, 0), Orows(n, 0);
	vector<int> Xcols(n, 0), Xrows(n, 0);
	
	vector<string> g(n);
	
	for(int i = 0; i < n; ++i) {
		cin >> g[i];
		for(int j = 0; j < n; ++j) {
			if(g[i][j] == 'X') ++Xcols[j], ++Xrows[i];
			else if(g[i][j] == 'O') ++Ocols[j], ++Orows[i];
		}
	}
	
	int cnt = 0, moves = INT_MAX;
	
	for(int i = 0; i < n; ++i) {
		if(!Ocols[i]) moves = min(moves, n - Xcols[i]);
		if(!Orows[i]) moves = min(moves, n - Xrows[i]);
	}
	
	if(moves == INT_MAX) {
		cout << "Impossible\n";
		return;
	}
	
	for(int i = 0; i < n; ++i) {
		if(!Ocols[i] && n - Xcols[i] == moves) {
			++cnt;
			if(moves == 1) {
				for(int k = 0; k < n; ++k) {
					if(g[k][i] == '.') {
						if(!Orows[k] && n - Xrows[k] == 1) --cnt;
						break;
					}
				}
			}
		}
		if(!Orows[i] && n - Xrows[i] == moves) ++cnt;
	}
	
	cout << moves << ' ' << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	for(int k = 1; k <= t; ++k) {
		cout << "Case #" << k << ": ";
		solve();
	}
 	return 0;
}
