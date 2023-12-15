#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("popcnt", "mmx", "sse", "sse2")
#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2e4;
int bits[MAXN];
void solve() {
	int n, k, ans = 31;
	cin >> n >> k;
	for(int i = 0; i < n; ++i) {
		string str;
		cin >> str;
		for(char c : str) bits[i] = (bits[i] << 1) + c - '0';
	}
	for(int i = 0; i < n; ++i)
	for(int j = i + 1; j < n; ++j)
		ans = min(ans, __builtin_popcount(bits[i] ^ bits[j]));
	cout << ans << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	solve();
	return 0;
}
