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

const int MAXC = 1e5 + 10;

int n, c, q, nColor[MAXC];
set<tuple<int, int, int>> cover;

void upd(int l, int r, int x) {
	vector<tuple<int, int, int>> new_covers;

	auto it = cover.lower_bound(make_tuple(l, -1, -1));

	new_covers.pb({l, r, x});

	if(it != cover.begin() && get<1>(*prev(it)) >= l) --it;
	
	while(it != cover.end() && get<0>(*it) <= r) {
		auto [lo, hi, x] = *it;
		if(lo < l) new_covers.pb({lo, l - 1, x});
		if(hi > r) new_covers.pb({r + 1, hi, x});
		nColor[x] -= hi - lo + 1;
		it = cover.erase(it);
	}

	for(auto [l, r, x] : new_covers) {
		nColor[x] += r - l + 1;
		cover.emplace(l, r, x);
	}
}

void solve() {
	cin >> n >> c >> q;

	cover.emplace(0, n - 1, 1);
	nColor[1] = n;

	while(q--) {
		int p, x, a, b;
		cin >> p >> x >> a >> b;
		int s = nColor[p];
		int l = (a + (i64)s * s) % n;
		int r = (a + (s + b) * (s + b + 0ll)) % n;
		if(l > r) swap(l, r);
		upd(l, r, x);
	}

	cout << *max_element(nColor, nColor + c + 1) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}