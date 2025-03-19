#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,mmx,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

const int maxn = 1e5, inf = 1e9 + 1;
int n, m, c[maxn], t_in, t[maxn], lo[maxn], dp[maxn], F[maxn], tot[maxn], CC[maxn], id;
vi g[maxn];

void cc(int v) {
	CC[v] = id;
	tot[id] += c[v];
	for(int u : g[v]) {
		if(CC[u] != -1) continue;
		cc(u);
	}
}

void dfs(int v) {
	int resto = tot[CC[v]] - c[v];
	t[v] = lo[v] = t_in++;
	dp[v] = c[v];
	for(int u : g[v]) {
		if(t[u] == -1) {
			dfs(u);
			if(lo[u] >= t[v]) {
				F[v] += max(0, dp[u]);
				resto -= dp[u];
			}
			dp[v] += dp[u];
			lo[v] = min(lo[v], lo[u]);
		} else
			lo[v] = min(lo[v], t[u]);
	}
	F[v] += max(0, resto);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for(int i = 0; i < n; ++i) {
		cin >> c[i];
		CC[i] = t[i] = -1;
	}
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for(int i = 0; i < n; ++i) {
		if(CC[i] != -1) continue;
		cc(i);
		++id;
	}
	for(int i = 0; i < n; ++i) {
		if(t[i] != -1) continue;
		dfs(i);
	}
	int S = 0;
	for(int i = 0; i < id; ++i) S += max(0, tot[i]);
	for(int i = 0; i < n - 1; ++i) cout << F[i] + (tot[CC[i]] > 0 ? S - tot[CC[i]] : S) << ' ';
	cout << F[n - 1] + (tot[CC[n - 1]] > 0 ? S - tot[CC[n - 1]] : S) << '\n';
	return 0;
}