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

const int N = 2e5 + 10;

int h[N], n, m;
set<ii> L, R;

void updL(int i, int h) {
	auto it = L.lower_bound({i, -1});
	while(it != L.end() && it->sc < h) it = L.erase(it);
	it = L.upper_bound({i + 1, -1});	
	if(it == L.begin() || prev(it)->sc < h) L.emplace(i, h);
}

void updR(int i, int h) {
	auto it = R.upper_bound({i + 1, -1});
	while(it != R.begin() && prev(it)->sc < h) it = R.erase(--it);
	it = R.upper_bound({i + 1, -1});
	if(it == R.end() || it->sc < h) R.emplace(i, h);
}

int query(char t, int i) {
	if(t == 'R') {	
		if(auto it = R.lower_bound({i, -1}); it != R.end() && it->fi == i) return i + 1;
		auto it = L.lower_bound({i + 1, -1});
		if(it != L.end()) return it->fi + 1;
		return prev(R.lower_bound({i, -1}))->fi + 1;
	}
	if(auto it = L.lower_bound({i, -1}); it != L.end() && it->fi == i) return i + 1;
	auto it = R.lower_bound({i, -1});
	if(it != R.begin()) return prev(it)->fi + 1;
	return L.lower_bound({i + 1, -1})->fi + 1;
}

void solve() {
	cin >> n >> m;

	for(int i = 0, mx = -INF; i < n; ++i) {
		cin >> h[i];
		if(mx < h[i]) L.emplace(i, h[i]);
		mx = max(mx, h[i]);
	}

	for(int i = n - 1, mx = -INF; i >= 0; --i) {
		if(mx < h[i]) R.emplace(i, h[i]);
		mx = max(mx, h[i]);
	}
	
	while(m--) {
		char t;
		int i, new_h;
		cin >> t >> i;
		--i;
		if(t == 'U') {
			cin >> new_h;
			updL(i, new_h);
			updR(i, new_h);
		} else cout << query(t, i) << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
