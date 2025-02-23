#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2,sse3")
#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

const int inf = 1e9;

int n, f;
vector<vector<pair<int, int>>> t;
vector<int> dp, custo, cnt;
vector<bool> amigo;

void dfs(int u, int pai, int cst) {
	dp[u] = inf;
	custo[u] = cnt[u] = 0;
	for(auto [v, c] : t[u]) {
		if(v == pai) continue;
		dfs(v, u, cst + c);
		cnt[u] += cnt[v];
		custo[u] += custo[v];
	}
	if(amigo[u] && custo[u] == 0) {
		cnt[u] = 1;
		dp[u] = 0;
		custo[u] = cst;
	} else if(cnt[u] > 0) {
		custo[u] -= (cnt[u] - 1) * cst;
		cnt[u] = 1;
		for(auto [v, c] : t[u]) {
			if(v == pai) continue;
			dp[u] = min(dp[u], custo[u] - custo[v] + dp[v]);
		}
	} else 
		dp[u] = 0;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> f;
	t.resize(n);
	dp.resize(n);
	custo.resize(n);
	cnt.resize(n);
	amigo.assign(n, false);
	for(int i = 1; i < n; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		t[a].push_back({b, c});
		t[b].push_back({a, c});
	}
	for(int i = 0; i < f; ++i) {
		int x; 
		cin >> x;
		amigo[x - 1] = true;
	}
	dfs(0, 0, 0);
	cout << dp[0] << '\n';
	return 0;
}