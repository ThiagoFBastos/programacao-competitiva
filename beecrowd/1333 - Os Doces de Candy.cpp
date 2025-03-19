#include "bits/stdc++.h"
using namespace std;
using ll = long long;
vector<int> c;
int n;
void euclides(int a, int b, ll& x, ll& y) {
	if(b == 0) x = 1, y = 0;
	else {
		ll x1, y1;
		euclides(b, a % b, x1, y1);
		y = x1 - a / b * y1;
		x = y1;
	}
}
int count(int x) {
	if(x < 2 || x > c[0] || x % n) return 0;
	int a = c[0] - x - x / n, b = x / n;
	int mod = a % x;
	if(a < 0) return 0;
	for(int v : c) if((v - x - b) % x != mod) return 0;
	int g = gcd(x, b), d;
	if(mod % g) return 0;
	ll p, q;
	x /= g;
	euclides(x, b / g, p, q);
	q = (q % x + x) % x;
	d = (mod / g + 0LL) * q % x;
	return (a / b - d) / x + 1;
}
void solve() {
	int g = 0;
	cin >> n;
	if(!n) exit(0);
	c.resize(n);
	for(int i = 0; i < n; ++i) cin >> c[i];
	sort(c.begin(), c.end());
	for(int i = 1; i < n; ++i) {
		if(c[i] != c[i - 1]) {
			g = c[i] - c[i - 1];
			break;
		}
	}
	vector<int> p;
	if(g) {
		for(int k = 1; k * k <= g; ++k) {
			if(g % k) continue;
			p.push_back(k);
			if(k * k != g) p.push_back(g / k);
		}
	} else {
		map<int, int> S;
		int x = c[0];
		p.push_back(1);
		for(int k = 2; k * k <= x; ++k) {
			if(x % k) continue;
			int cnt = 0;
			while(x % k == 0) {
				x /= k;
				++cnt;
			}
			S[k] += cnt;
		}
		if(x > 1) ++S[x];
		x = n;
		for(int k = 2; k * k <= x; ++k) {
			if(x % k) continue;
			int cnt = 0;
			while(x % k == 0) {
				x /= k;
				++cnt;
			}
			S[k] += cnt;
		}
		if(x > 1) ++S[x];
		for(auto& x : S) {
			int sz = p.size();
			auto q = 1LL;
			for(int i = 0; i < x.second; ++i) {
				q *= x.first;
				for(int j = 0; j < sz; ++j) if(p[j] * q <= c[0]) p.push_back(p[j] * q);
			}	
		}
	}
	auto ans = 0LL;
	for(int x : p) ans += count(x);
	cout << ans << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	for(;;) solve();
	return 0;
}