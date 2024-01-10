#include "bits/stdc++.h"
using namespace std;

const int N = 1e2;

int g[N][N];

void solve() {

	int n, k;
	
	cin >> n >> k;
	
	int cnt = (n - 1) * (n - 2) / 2, edges = n - 1;
	
	if(k > cnt) {
		cout << "-1\n";
		return;
	}
	
	for(int i = 1; i < n; ++i) g[0][i] = g[i][0] = 1;
	
	for(int i = 1; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			if(j == i || g[i][j]) continue;
			else if(k < cnt) {
				g[i][j] = g[j][i] = 1;
				--cnt, ++edges;
			}
		}
	}
	
	cout << edges << '\n';
	
	for(int i = 0; i < n; ++i)
	for(int j = i + 1; j < n; ++j)
		if(g[i][j]) cout << i + 1 << ' ' << j + 1 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
