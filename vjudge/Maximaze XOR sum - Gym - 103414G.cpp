#include "bits/stdc++.h"

using namespace std;

int msb(long long x) {
	return 63 - __builtin_clzll(x);
}

void solve() {
	int n;

	cin >> n;

	vector<long long> a(n), b(n);
	vector<pair<long long, int>> c[64], base;
	vector<unordered_map<int, int>> sub(n);
	unordered_map<int, int> ans;
	
	long long x = 0, y = 0;

	for(long long& v : a) {
		cin >> v;
		x ^= v;
	}

	for(long long& v : b) {
		cin >> v;
		x ^= v;
	}

	for(int i = 0; i < n; ++i) {
		sub[i][i] = 1;
		a[i] &= ~x;
		b[i] &= ~x;
		y ^= a[i];
		long long z = a[i] ^ b[i];
		if(!z) continue;
		int l = msb(z);
		c[l].emplace_back(z, i);
	}

	for(int i = 60; i >= 0; --i) {
		auto& X = c[i];

		if(X.empty()) continue;
	
		auto [v, k] = X[0];

		base.emplace_back(a[k] ^ b[k], k);

		for(auto [u, j] : X) {
			u ^= v;
			if(!u) continue;
			int l = msb(u);
			c[l].emplace_back(u, j);
		}
	}

	for(int i = 0; i < (int)base.size(); ++i) {

		for(int k = i; k < (int)base.size(); ++k) {
			if(base[i] < base[k])
				swap(base[k], base[i]);
		}

		auto [u, l] = base[i];
	
		if((y ^ u) > y) {
			y ^= u;
			for(auto [pos, _] : sub[l]) if(++ans[pos] == 2) ans.erase(pos);
		}

		for(int k = i + 1; k < (int)base.size(); ++k) {
			auto& [v, j] = base[k];
	
			if(msb(u) != msb(v)) continue;

			v ^= u;

			for(auto [pos, _] : sub[l]) if(++sub[j][pos] == 2) sub[j].erase(pos);
		}
	}

	cout << x + 2 * y << ' ' << ans.size() << '\n';
	for(auto [k, _] : ans) cout << k + 1 << ' ';
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}