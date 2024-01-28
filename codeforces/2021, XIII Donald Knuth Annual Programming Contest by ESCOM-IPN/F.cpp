#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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

void solve() {
		
	i64 n;
	int m;

	cin >> n >> m;

	vector<pair<i64, i64>> p(m);

	for(auto& [x, y] : p) cin >> x >> y;
	
	auto check = [&](auto st) {
		i64 lo = 1;
		for(auto [l, r, id] : st) {
			if(lo < l) return false;
			lo = max(lo, r + 1);
		}
		return lo == n + 1;
	};

	i64 l = 0, r = n;
	
	while(l < r) {
		i64 d = (l + r) / 2;

		map<i64, vector<tuple<i64, i64, int, int>>> mp;
		set<tuple<i64, i64, int>> st;

		for(int i = 0; i < m; ++i) {	
			auto [x, y] = p[i];
			i64 lx = max(1ll, x - d), rx = min(n, x + d);
			i64 ly = max(1ll, y - d), ry = min(n, y + d);
			mp[ly].pb({lx, rx, 1, i});
			if(ry + 1 <= n) mp[ry + 1].pb({lx, rx, 0, i});
		}
		
		bool ok = true;

		for(auto& [y, v] : mp) {
			for(auto [l, r, type, id] : v) {
				if(type == 1) st.emplace(l, r, id);
				else st.erase(make_tuple(l, r, id));
			}
			ok = ok && check(st);
		}

		if(ok) r = d;
		else l = d + 1;
	}

	cout << r << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

