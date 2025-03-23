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

void solve() {	
	int n;
	cin >> n;
	vector<vector<int>> adj(n);
	map<vector<int>, int> mp;
	vector<bool> sym(n, false);
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b); adj[b].pb(a);
	}
	auto dfs = [&](auto& self, int u, int p)->int {
		vector<int> h;
		vector<ii> H;
		int deg = (int)adj[u].size() - (p != -1);
		for(int v : adj[u]) {
			if(v == p) continue;
			int hsh = self(self, v, u);
			h.pb(hsh);
			H.pb({hsh, v});	
		}
		sort(all(h));
		if(deg % 2) {
			vector<bool> pref(deg, false), suf(deg, false);
			sort(all(H));
			for(int i = 1; i < deg; ++i) {
				pref[i] = H[i].fi == H[i - 1].fi;
				if(i >= 2) pref[i] = pref[i] && pref[i - 2];
			}
			for(int i = deg - 2; i >= 0; --i) {
				suf[i] = H[i].fi == H[i + 1].fi;
				if(i + 2 < deg) suf[i] = suf[i] && suf[i + 2];
			}
			for(int i = 0; i < deg; ++i) {
				bool ok;
				if(i % 2 == 0) ok = (!i || pref[i - 1]) && (i == deg - 1 || suf[i + 1]);
				else ok = (i < 3 || pref[i - 2]) && (i >= deg - 3 || suf[i + 2]) && H[i-1].fi == H[i+1].fi;
				if(ok) sym[u] = sym[u] || sym[H[i].sc];
			}
		} else {
			sym[u] = true;
			for(int i = 0; i < deg; i += 2) sym[u] = sym[u] && h[i] == h[i + 1];
		}
		if(!mp.count(h)) return mp[h] = mp.size();
		return mp[h];
	};
	(void)dfs(dfs, 0, -1);
	cout << (sym[0] ? "YES\n" : "NO\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
