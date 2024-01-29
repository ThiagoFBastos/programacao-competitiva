#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ii = pair<int, int>;
using ld = long double;

void solve() {
	
	int n, m;

	cin >> n;

	set<tuple<int, int, int>> S;
	map<int, set<int>> P;
	vector<int> c(n);
	int cur = 0;

	for(int i = 0; i < n; ++i) {
		cin >> c[i];
		P[c[i]].insert(i);
		if(c[i] != c[cur]) {
			S.insert(make_tuple(cur, i - 1, c[cur]));
			cur = i;
		}
	}

	S.insert(make_tuple(cur, n - 1, c[cur]));

	cin >> m;

	while(m--) {
		int v;
		cin >> v;

		auto K = P.find(v);

		if(K == P.end() || K->second.empty()) continue;

		auto& p = K->second;

		int l = *p.begin(), r = *p.rbegin();
		
		auto it = S.lower_bound(make_tuple(l, -1, -1));
		
		while(it != S.end()) {
			auto [lo, hi, cls] = *it;
			if(lo > r) break;
			auto L = P[cls].lower_bound(lo);
			auto R = P[cls].upper_bound(hi);
			P[cls].erase(L, R);
			it = S.erase(it);
		}

		S.insert(make_tuple(l, r, v));
	}

	for(auto [l, r, c] : S) {
		for(; l <= r; ++l) cout << c << ' ';
	}

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

