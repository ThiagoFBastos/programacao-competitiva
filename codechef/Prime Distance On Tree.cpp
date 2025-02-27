#include <bits/stdc++.h>

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

int is_prime(int x) {
	if(x < 2) return 0;
	for(int k=2;k * k <= x; ++k) if(x % k == 0) return 0;
	return 1;
}

const int N = 5e4 + 100;

int n, sz[N], depth[N];
i64 pairs;
vector<int> P, g[N];

int findCentroid(int u, int p) {
	sz[u] = 1;
	for(auto v : g[u]) {
		if(v == p) continue;
		(void)findCentroid(v, u);
		sz[u] += sz[v];
	}
	if(u == p) {
		int n = sz[u];
		while(true) {
			ii x(n - sz[u], p);
			for(auto v : g[u]) {
				if(v == p) continue;
				x = max(x, ii(sz[v], v));
			}
			if(x.first <= n / 2) break;
			p = u, u = x.second;
		}
		return u;
	}
	return -1;
}
 
int S[N], frq[N];

void dfs(int c, int u, int p) {
	int i = -1;

	sz[u] = 1;

	if(u == p) {
		depth[u] = 0;
		++frq[0];
	} else ++S[depth[u]];

	for(int k = 0; k < (int)g[u].size(); ++k) {
		int v = g[u][k];
	
		if(v == c) i = k;
		if(v == p) continue;

		depth[v] = 1 + depth[u];
		dfs(c, v, u);
		sz[u] += sz[v];

		if(u == p) {	
			for(int i = 1; i < n && S[i]; ++i) {
				for(int z : P) {
					if(z < i) break;
					pairs += (i64)S[i] * frq[z - i];
				}
			}
			for(int i = 1; i < n && S[i]; ++i) {
				frq[i] += S[i];
				S[i] = 0;
			}			
		}
	}

	if(i != -1) {
		swap(g[u][i], g[u].back());
		g[u].pop_back();
	}

	if(u == p) for(int i = 0; i < n && frq[i]; ++i) frq[i] = 0;
}

void rec(int u) {
	u = findCentroid(u, u);
	dfs(u, u, u);
	for(int v : g[u]) rec(v);
}

void solve() {
	cin >> n;
	for(int i = n; i; --i) if(is_prime(i)) P.push_back(i);
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}	
	rec(0);
	i64 m = n * (n - 1ll) / 2;
	cout << fixed << setprecision(9) << 1.0L * pairs / m << '\n';
}		
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}