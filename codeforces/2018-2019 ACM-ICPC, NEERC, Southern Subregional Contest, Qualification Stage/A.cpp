#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ii = pair<int, int>;
using ld = long double;

void solve() {
	
	int n, m, d;

	cin >> n >> m >> d;

	vector<int> day(n);
	set<ii> s;
	int cur_day = 1;

	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		s.insert(ii(x, i));
	}

	while(!s.empty()) {
		auto [t, k] = *s.begin();
		s.erase(s.begin());
		day[k] = cur_day;
		while(!s.empty()) {
			auto it = s.lower_bound(ii(t + d + 1, -1));
			if(it == s.end()) break;
			day[it->second] = cur_day;
			t = it->first;
			s.erase(it);
		}
		++cur_day;
	}

	cout << cur_day - 1 << '\n';

	for(int v : day) cout << v << ' ';
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

