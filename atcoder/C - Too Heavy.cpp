#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n;

	cin >> n;

	vector<int> a(n), b(n), p(n);

	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;
	for(int& v : p) {
		cin >> v;
		--v;
	}

	vector<int> who(n);
	set<ii> s;
	vector<ii> swaps;

	for(int i = 0; i < n; ++i) {
		who[p[i]] = i;
		if(a[i] <= b[p[i]]) {
			if(p[i] != i) {
				cout << "-1\n";
				return;
			}
		} else s.emplace(b[p[i]], i);
	}

	while(!s.empty()) {
		auto [x, i] = *s.begin();
		s.erase(s.begin());
		if(who[i] == i) continue;
		swaps.emplace_back(i + 1, 1 + who[i]);
		s.erase(ii(b[i], who[i]));
		s.emplace(x, who[i]);
		who[p[i]] = who[i];
		swap(p[i], p[who[i]]);
	}
  
	cout << swaps.size() << '\n';
	for(auto [x, y] : swaps) cout << x << ' ' << y << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
