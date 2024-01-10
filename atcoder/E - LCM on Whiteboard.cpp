#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	
	int n;

	cin >> n;

	vector<vector<ii>> a(n);
	map<int, set<ii>> S;	
	set<vector<ii>> out;

	for(int i = 0; i < n; ++i) {
		int m;
		cin >> m;
		a[i].resize(m);
		for(auto& [p, c] : a[i]) {
			cin >> p >> c;
			S[p].insert(ii(c, i));
		}
	}

	for(int i = 0; i < n; ++i) {
		vector<ii> K;
		for(auto [p, c] : a[i]) {
			auto& X = S[p];
			int c1 = X.rbegin()->first;
			X.erase(ii(c, i));
			int c2 = X.empty() ? 0 : X.rbegin()->first;	
			if(c1 != c2) K.emplace_back(p, c1 - c2);
			X.insert(ii(c, i));
		}
		sort(K.begin(), K.end());
		out.insert(K);
	}

	cout << size(out) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
