#pragma GCC optimize("O3")
#pragma GCC target("popcnt", "mmx", "sse", "sse2", "sse3", "sse4")
#include "bits/stdc++.h"
using namespace std;
const int MAXN = 3e3;
bitset<MAXN> g[MAXN];
void solve() {
	int n;
	long long cnt = 0;
	cin >> n;
	for(int i = 0; i < n; ++i) {
		string str;
		cin >> str;
		for(int j = 0; j < n; ++j)
			g[i][j] = str[j] - '0';
	}
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			int bits = (g[i] & g[j]).count();
			cnt += bits * (bits - 1) / 2; 
		}
	}
	cout << cnt << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	solve();
	return 0;
}
