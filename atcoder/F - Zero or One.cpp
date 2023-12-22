#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

int is_good(i64 n, int b) {
	int ans = 1;
	for(; n > 0; n /= b) ans = ans && n % b <= 1;
	return ans;
}

void get(int mask, i64& a, i64& b, i64& c, i64& d) {
	a = !!(mask & 8);
	b = !!(mask & 4);
	c = !!(mask & 2);
	d = !!(mask & 1);
}

i64 f(i64 x, i64 a, i64 b, i64 c, i64 d) {
	return a * x * x * x + b * x * x + c * x + d;
}

i64 root(i64 n, i64 a, i64 b, i64 c, i64 d) {
	i64 lo, hi;
	if(a) {
		lo = 0, hi = 1e6;
		while(lo < hi) {
			i64 m = (lo + hi) / 2;
			if(f(m, a, b, c, d) >= n) hi = m;
			else lo = m + 1;
		}
	} else if(b) {
		lo = 0, hi = 1e9;
		while(lo < hi) {
			i64 m = (lo + hi) / 2;
			if(f(m, a, b, c, d) >= n) hi = m;
			else lo = m + 1;
		}
	} else {
		lo = 0, hi = 1e18L;
		while(lo < hi) {
			i64 m = (lo + hi) / 2;
			if(f(m, a, b, c, d) >= n) hi = m;
			else lo = m + 1;
		}
	}
	if(f(hi, a, b, c, d) == n) return hi;
	return -1;
}

void solve() {
	i64 n;
	int cnt = 0;

	cin >> n;

	for(int i = 2; i <= 40000; ++i) cnt += is_good(n, i);

	for(int k = 0; k < 16; ++k) {
		i64 a, b, c, d;
		get(k, a, b, c, d);
		if(a + b + c == 0) continue;
		cnt += root(n, a, b, c, d) > 40000;
	}

	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}

