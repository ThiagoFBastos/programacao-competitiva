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
 
const int p[2] = {31, 19};
const int mod[2] = {(1LL << 31) - 1, (1 << 19) - 1};
const int base[2] = {1919, 1717};
const int N = 2e6 + 1;
 
string s, suf;
int h[2][N], pot[2][N];
 
i64 expmod(i64 n, int p, int mod) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}
 
int get_mod(int k, i64 x) {
	if(x < 0) x += mod[k];
	x = (x & mod[k]) + (x >> p[k]);
	return x >= mod[k] ? x - mod[k] : x;
}
 
void create_hash() {
	int n = suf.size();
	for(int i = 0; i < 2; ++i) {
		i64 p = 1, b = expmod(base[i], mod[i] - 2, mod[i]);
		pot[i][0] = 1;
		for(int k = 1; k <= n; ++k) {
			p = get_mod(i, p * base[i]);
			pot[i][k] = get_mod(i, pot[i][k - 1] * b);
			h[i][k] = get_mod(i, h[i][k - 1] + p * (suf[k - 1] - 'a' + 1));
		}
	}
}
 
int query(int k, int l, int r) {
	i64 x = h[k][r] - h[k][l - 1];
	if(x < 0) x += mod[k];
	x *= pot[k][l - 1];
	x = (x & mod[k]) + (x >> p[k]);
	return x >= mod[k] ? x - mod[k] : x;
}
 
ii query(int l, int r) {
	return {query(0, l + 1, r + 1), query(1, l + 1, r + 1)};
}
 
bool cmp(int a, int b) {
	int lo = 0, hi = (int)s.size();
	while(lo < hi) {
		int mid = (lo + hi) >> 1;
		if(query(a, a + mid) != query(b, b + mid)) hi = mid;
		else lo = mid + 1;
	}
	return suf[a + hi] < suf[b + hi];
}
 
void solve() {
	string col;
	int k = 0;
	cin >> s;
	suf = s + s;
	create_hash();
	for(int i = 1; i < (int)s.size(); ++i) if(cmp(i, k)) k = i;
	cout << suf.substr(k, (int)s.size()) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
