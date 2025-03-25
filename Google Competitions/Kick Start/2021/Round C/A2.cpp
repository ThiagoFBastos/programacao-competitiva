#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7;
int caso;
auto exp(long long n, int p) {
	auto ans = 1LL;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = n * ans % mod;
		n = n * n % mod;
	}
	return ans;
}
void solve() {
	int n, k;
	string s;
	cin >> n >> k >> s;
	int mid = (n + 1) / 2, cnt = 0;
	for(int i = 0; i < mid; ++i) cnt = (cnt + (s[i] - 'a') * exp(k, mid - i - 1)) % mod;
	string r = s.substr(0, mid);
	string v = r;
	if(n % 2) r.pop_back();
	reverse(r.begin(), r.end());
	v += r;
	cout << "Case #" << caso << ": " << (cnt + (v < s)) % mod << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	for(caso = 1; caso <= t; ++caso) solve();
	return 0;
}