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

const int N = 5e4 + 10;

vector<int> adj[N];
vector<ii> delta;
int n, m[2], c[N];

void dfs(int u) {
	++m[c[u]];
	for(int v : adj[u]) {
		if(c[v] < 0) {
			c[v] = 1 ^ c[u];
			dfs(v);
		}
	}
}

void solve() {

	for(int a = -5; a <= 5; ++a)
	for(int b = -5; b <= 5; ++b)
		if(a*a+b*b<=25) delta.pb({a, b});

	cin >> n;

	map<ii, int> mp;

	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		for(auto [dx, dy] : delta) {
			auto it = mp.find(ii(x+dx,y+dy));
			if(it == mp.end()) continue;
			adj[i].pb(it->sc);
			adj[it->sc].pb(i);
		}
		mp[{x,y}] = i;
	}

	memset(c, -1, n * sizeof(int));

	int ans = 0;

	for(int i = 0; i < n; ++i) {
		if(c[i] != -1) continue;
		c[i] = m[0] = m[1] = 0;
		dfs(i);
		ans += min(m[0], m[1]);
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}