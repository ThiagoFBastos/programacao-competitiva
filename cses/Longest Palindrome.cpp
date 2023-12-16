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
 
i64 exp(i64 n, i64 p, i64 mod) {
	__int128 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = (__int128)ans * n % mod;
		n = (__int128)n * n % mod;
	}
	return (i64)ans;
}
 
const i64 mod = (1LL << 61) - 1;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
i64 seed = rng();
 
string s, rs;
 
i64 get_mod(__int128 x) {
	x = (x & mod) + (x >> 61);
	if(x >= mod) x -= mod;
	return (i64)x;
}
 
struct str_hash {
	vector<i64> h, ip;
	str_hash() {}
	str_hash(string& s) {
		int n = s.size();
		i64 k = seed, ik = exp(k, mod - 2, mod), p = 1;
		h.resize(n + 1);
		ip.resize(n + 1);
		h[0] = 0, ip[0] = 1;
		for(int i = 1; i <= n; ++i) {
			p = get_mod((__int128)p * k);
			ip[i] = get_mod((__int128)ip[i - 1] * ik);
			h[i] = get_mod(h[i - 1] + (__int128)(s[i - 1] - 'a' + 1) * p);
		}
	}
	i64 query(int l, int r) {
		i64 v = h[r + 1] - h[l];
		if(v < 0) v += mod;
		return get_mod((__int128)v * ip[l]); 
	}
};
 
str_hash S, RS;
 
int max_len(int i, int j, int n) {
	int lo = 0, hi = min(i, n - j - 1) + 1;
	while(lo < hi) {
		int mid = (lo + hi) / 2;
		if(S.query(i - mid, i) != RS.query(n - 1 - j - mid, n - 1 - j)) hi = mid;
		else lo = mid + 1;
	}
	return hi - 1;
}
 
void solve() {
	
	cin >> s;
	
	rs = string(s.rbegin(), s.rend());
	
	S = str_hash(s);
	RS = str_hash(rs);
	
	int n = s.size();
	auto ans = make_tuple(0, 0, 0);
	
	for(int i = 0; i < n; ++i) {
		int L = max_len(i, i, n);
		ans = max(ans, make_tuple(2 * L + 1, i - L, i + L));
		if(s[i] != s[i + 1]) continue;
		L = max_len(i, i + 1, n);
		ans = max(ans, make_tuple(2 * (L + 1), i - L, i + 1 + L));
	}
	
	auto [k, l, r] = ans;
	cout << s.substr(l, k) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
