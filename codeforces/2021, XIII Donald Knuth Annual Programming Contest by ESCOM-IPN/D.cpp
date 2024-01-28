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

struct event {
	int x;
	int type;
	int id;
};

bool operator<(event e1, event e2) {
	if(e1.x != e2.x) return e1.x < e2.x;
	return e1.type < e2.type;
}

void solve() {
	int n, m, q;

	cin >> n >> m >> q;

	vector<int> l(m), r(m), u(q), v(q);
	vector<event> e;
	vector<bool> check(q, false);
	multiset<int> R;

	for(int i = 0; i < m; ++i) {
		cin >> l[i] >> r[i];
		e.pb({l[i], 1, i});
		e.pb({r[i] + 1, 0, i});
	}

	for(int i = 0; i < q; ++i) {
		cin >> u[i] >> v[i];
		if(u[i] > v[i]) swap(u[i], v[i]);
		e.pb({u[i], 2, i});
	}

	sort(all(e));

	for(auto [x, type, id] : e) {
		if(type == 0) R.erase(R.find(r[id]));
		else if(type == 1) R.insert(r[id]);
		else check[id] = !R.empty() && *R.rbegin() >= v[id];
	}

	for(bool ans : check) cout << (ans ? "Yes\n" : "No\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

