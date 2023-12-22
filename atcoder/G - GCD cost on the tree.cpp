#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int mod = 998244353;
const int MAXN = 1e5 + 100;

vector<int> adj[MAXN], d[MAXN], S[MAXN];
int n, a[MAXN], last[MAXN], sub[MAXN];
i64 cnt[MAXN];

void dfs(int u, int g) {
	last[u] = g;
	sub[u] = 1;
	for(int v : adj[u]) {
		if(last[v] == g || a[v] % g) continue;
		dfs(v, g);
		sub[u] += sub[v];
	}
}

void get(int n, int g, int u, int p) {
	for(int v : adj[u]) {
		if(v == p || last[v] != g) continue;
		get(n, g, v, u);
		cnt[g] = (cnt[g] + (n - sub[v] + 0ll) * sub[v]) % mod;
	}
}

void solve() {
	cin >> n;
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		S[a[i]].push_back(i);
	}
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i = 1; i < MAXN; ++i)
		for(int j = i; j < MAXN; j += i)
			for(int k : S[j])
				d[i].push_back(k);
	int ans = 0;
	for(int i = MAXN - 1; i; --i) {
		if(d[i].empty()) continue;
		for(int k : d[i]) {
			if(last[k] == i) continue;
			dfs(k, i);
			get(sub[k], i, k, k);
			cnt[i] = (cnt[i] + (sub[k] - 1ll) * sub[k] / 2) % mod;
		}
		for(int k = 2 * i; k < MAXN; k += i) {
			cnt[i] -= cnt[k];
			if(cnt[i] < 0) cnt[i] += mod;
		}
		ans = (ans + i * cnt[i]) % mod;
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
