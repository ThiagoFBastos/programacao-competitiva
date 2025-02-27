#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 1, mod = 1e9 + 7;

int mobius[N], p[N];

auto divisores(int x) {
	vector<int> v {1};
	while(x > 1) {
		int n = size(v), px = p[x];
		auto k = 1LL;
		while(p[x] == px) {
			k *= px;
			for(int i = 0; i < n; ++i) v.push_back(v[i] * k);
			x /= px;
		}
	}
	return v;
}

void solve() {
	
	int n, m, l, r, ans = 0;
	
	cin >> n >> m >> l >> r;
  
  	for(int k = 2; k * k <= r; ++k) {
  		if(p[k]) continue;
  		for(int i = k; i <= r; i += k) p[i] = k;
  	}
  	
  	mobius[1] = -1;
  	
  	for(int k = 2; k <= r; ++k) {
  		if(!p[k]) p[k] = k;
  		if(k % (1LL * p[k] * p[k]) == 0) mobius[k] = 0;
  		else mobius[k] = -mobius[k / p[k]];
  	}
  	
  	mobius[1] = 0;
  	
	for(int a = 1; a < n && a <= r; ++a) {
		int L = ceil(sqrt(max(1LL, 1ll * l * l - 1ll * a * a)));
		int R = min(m - 1, (int)floor(sqrt(1ll * r * r - 1ll * a * a)));

		if(L > R) continue;
		
		auto S = (R - L + 1LL) * (R + L) / 2;
		int cnt = R - L + 1;
		
		for(int x : divisores(a)) {
			int e = (L - 1) / x, d = R / x;
			cnt -= mobius[x] * (d - e);
			S -= ((e + d) * (d - e + 1LL) / 2 - e) * x * mobius[x];
		}
		
		ans = (ans + 2 * (1LL * m * cnt - S) % mod * (n - a)) % mod;
	}
	
	if(l == 1) ans = (ans + (n - 1LL) * m + (m - 1LL) * n) % mod;
	
	cout << (ans + mod) % mod << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}