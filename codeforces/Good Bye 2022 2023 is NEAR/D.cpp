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

const int N = 1e5 + 10, MOD = 998244353;

multiset<int> adj[N];
bool vis[N];
int n, a[N], b[N], ans;

void solve() {
	cin >> n;

	ans = 1;

	for(int i = 1; i <= n; ++i) {
		adj[i].clear();
		vis[i] = false;
	}

	for(int i = 0; i < n; ++i) cin >> a[i];

	queue<int> q;

	for(int i = 0; i < n; ++i) {
		cin >> b[i];
		if(a[i] == b[i]) {
			if(!vis[a[i]]) {
				ans = (i64)ans * n % MOD;
				q.push(a[i]);
			}
			vis[a[i]] = true;
		} else {
			adj[a[i]].insert(b[i]);
			adj[b[i]].insert(a[i]);
		}
	}

	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : adj[u]) {
			adj[v].erase(adj[v].find(u));
			if(vis[v]) continue;
			vis[v] = true;
			q.push(v);
		}
		adj[u].clear();
	}

	for(int i = 1; i <= n; ++i) {
		if((int)adj[i].size() == 1) {
			vis[i] = true;
			q.push(i);
		}
	}

	while(!q.empty()) {
		int u = q.front(); q.pop();
		if((int)adj[u].size() != 1) ans = 0;
		for(int v : adj[u]) {
			adj[v].erase(adj[v].find(u));
			if(vis[v] || (int)adj[v].size() != 1) continue;
			vis[v] = true;
			q.push(v);
		}
		adj[u].clear();
	}

	for(int i = 1; i <= n; ++i) {
		if(!vis[i] && (int)adj[i].size() != 2) {
			ans = 0;
			break;
		}
	}

	for(int i = 1; i <= n; ++i) {
		if(vis[i]) continue;
		ans = 2ll * ans % MOD;
		q.push(i);
		vis[i] = true;
		while(!q.empty()) {
			int i = q.front(); q.pop();
			for(int j : adj[i]) {
				if(vis[j]) continue;
				vis[j] = true;
				q.push(j);
			}
		}
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}

