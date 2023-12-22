#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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

using TYPE = pair<vector<int>, vector<ii>>;

vector<int> adj[N], path;
vector<ii> query[N];
vector<TYPE> sub;
int n, q, ans[N];

void dfs(vector<ii>& q, vector<int>& mp, int u, int p, int d) {

	path.pb(u);

	for(int v : adj[u]) {
		if(v == p) continue;
		vector<int> np;
		dfs(q, np, v, u, d + 1);
		if(mp.size() < np.size()) swap(mp, np);
	}

	path.pop_back();

	for(auto& x : query[u]) {
		if(x.fi <= d) ans[x.sc] = *(path.end() - x.fi) + 1;
		else {
			x.fi -= d;
			q.pb(x);
		}
	}

	mp.pb(u);
}

int C() {
	vector<int> deg(n, 0), t(n);
	queue<int> q;
	for(int i = 0; i < n; ++i) {
		deg[i] = adj[i].size();
		if(deg[i] <= 1) {
			t[i] = 0;
			q.push(i);
		}
	}
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int v : adj[u]) {
			if(--deg[v] != 1) continue;
			t[v] = 1 + t[u];
			q.push(v);
		}
	}
	return max_element(all(t)) - t.begin();
}

void solve() {
	cin >> n;

	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	int c = C();

	cin >> q;

	for(int i = 0; i < q; ++i) {
		int u, k;
		cin >> u >> k;
		--u;
		query[u].pb({k, i});
		ans[i] = -1;
	}

	path.pb(c);

	for(int v : adj[c]) {
		vector<ii> q;
		vector<int> mp;
		dfs(q, mp, v, c, 1);
		mp.pb(c);
		reverse(all(mp));
		sub.emplace_back(mp, q);
	}
	
	sort(all(sub), [](const auto& a, const auto& b) {
		return a.fi.size() > b.fi.size();
	});

	for(auto [k, j] : query[c]) {
		auto& P = sub[0].fi;
		if((int)P.size() <= k) continue;
		ans[j] = P[k] + 1;
	}

	if((int)sub.size() > 1) {
		for(int i = 0; i < (int)sub.size(); ++i) {
			for(auto [k, j] : sub[i].sc) {
				auto& P = i ? sub[0].fi : sub[1].fi;
				if((int)P.size() <= k) continue;
				ans[j] = P[k] + 1;
			}
		}
	}

	for(int i = 0; i < q; ++i) cout << ans[i] << '\n';
}		

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
