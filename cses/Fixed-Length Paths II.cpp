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
 
int n, k1, k2, sz[N], cnt[N];
vector<int> adj[N];
 
void fix(int u, int p) {
	if(p == -1) return;
	for(int& v : adj[u]) if(v == p) swap(v, adj[u].back());
	adj[u].pop_back();
}
 
int dfssz(int u, int p, int d = 0) {
	sz[u] = 1;
	++cnt[d];
	for(int v : adj[u]) {
		if(v == p) continue;
		(void)dfssz(v, u, d + 1);
		sz[u] += sz[v];
	}
	if(p != -1) return -1;
	int n = sz[u];
	while(true) {
		int v = -1, m = 0;
		for(int x : adj[u]) if(x != p && sz[x] > m) v = x, m = sz[x];
		if(2 * max(m, n - sz[u]) <= n) break;
		p = u, u = v;
	}
	return u;
}
 
i64 countPathsSub(int d, int frq[]) {
	i64 ans = 0;
	int lo = 0, hi = 0, tot = 0;
	for(int i = d; i >= 0; --i) {
		int l = max(0, k1 - i), r = min(d, k2 - i);
		if(l > r) continue;
		while(hi <= r) tot += frq[hi++];
		while(lo < l) tot -= frq[lo++];
		ans += (i64)tot * frq[i];
		if(i >= l && i <= r) ans += frq[i];
	}
	return ans;
}
 
void countHeights(int u, int p, int d = 0) {
	++cnt[d];
	for(int v : adj[u]) {
		if(v == p) continue;
		countHeights(v, u, d + 1);
	}
}
 
i64 countPaths(int u, int p) {
	i64 ans = 0;
 
	fix(u, p);
 
	int c = dfssz(u, -1), n = sz[u];
 
	if(p != -1) {
		for(int i = n - 1; i >= 0; --i) cnt[i + 1] = cnt[i];
		cnt[0] = 0;
		ans -= countPathsSub(n, cnt);
	}
 
	memset(cnt, 0, sizeof(int) * n);
	countHeights(c, -1);
	ans += countPathsSub(n - 1, cnt);
 
	memset(cnt, 0, sizeof(int) * (n + 1));
 
	for(int v : adj[c]) ans += countPaths(v, c);
 
	return ans;
}
 
int main(int argc, char* argv[]) {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n >> k1 >> k2;
 
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b); adj[b].pb(a);
	}
 
	cout << countPaths(0, -1) / 2 << '\n';
 
	return 0;
}
