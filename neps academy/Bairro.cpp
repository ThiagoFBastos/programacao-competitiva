#include "bits/stdc++.h"
using namespace std;
int n, k, tms;
vector<vector<int>> g;
vector<int> l, r, h;
void dfs(int u, int p = -1) {
	l[u] = r[u] = tms++;
	for(int v : g[u]) {
		if(v == p) continue;
		h[v] = 1 + h[u];
		dfs(v, u);
		r[u] = max(r[u], r[v]);
	}	
}
vector<vector<int>> cnt;
vector<int> dfs_array, skip;
int ans, blocos, szbloco;
void create() {
	szbloco = sqrt(n) + 1;
	blocos = (n + szbloco - 1) / szbloco;
	cnt = vector<vector<int>>(blocos, vector<int>(n + 1, 0));
	skip.assign(blocos, 0);
	dfs_array.resize(n);
	for(int i = 0; i < n; ++i) {
		dfs_array[l[i]] = h[i];
		++cnt[l[i] / szbloco][h[i]];
		if(h[i] <= k / 2) ++ans;
	}
}
void reset(int i) {
	int lo = i * szbloco, hi = (i + 1) * szbloco;
	for(; lo < hi; ++lo) {
		--cnt[i][dfs_array[lo]];
		dfs_array[lo] += skip[i];
		++cnt[i][dfs_array[lo]];
	}
	skip[i] = 0;
}
void menos(int i, int lo, int hi) {
	for(; lo <= hi; ++lo) {
		--cnt[i][dfs_array[lo]];
		if(--dfs_array[lo] == k / 2) ++ans;
		++cnt[i][dfs_array[lo]];
	}
}
void menos(int l, int r) {
	if(l > r) return;
	int L = l / szbloco, R = r / szbloco, v = k / 2;
	for(int i = L + 1; i < R; ++i) {
		int u = v + 1 - skip[i];
		if(u >= 0 && u < n) ans += cnt[i][u];
		--skip[i];
	}
	if(skip[L]) reset(L);
	if(skip[R]) reset(R);
	menos(L, l, min(min(r, n - 1), (L + 1) * szbloco - 1));
	if(L != R) menos(R, R * szbloco, r);
}
void soma(int i, int lo, int hi) {
	for(; lo <= hi; ++lo) {
		--cnt[i][dfs_array[lo]];
		if(dfs_array[lo]++ == k / 2) --ans;
		++cnt[i][dfs_array[lo]];
	}
}
void soma(int l, int r) {
	if(l > r) return;
	int L = l / szbloco, R = r / szbloco, v = k / 2;
	for(int i = L + 1; i < R; ++i) {
		int u = v - skip[i];
		if(u >= 0 && u < n) ans -= cnt[i][u];
		++skip[i];
	}
	if(skip[L]) reset(L);
	if(skip[R]) reset(R);
	soma(L, l, min(min(r, n - 1), (L + 1) * szbloco - 1));
	if(L != R) soma(R, R * szbloco, r);
}
int query(int l, int r, int x) {
	int ans = 0, L = l / szbloco, R = r / szbloco;
	for(int i = L + 1; i < R; ++i) {
		int h = x - skip[i];
		if(h >= 0 && h < n) ans += cnt[i][h];
	}
	if(skip[L]) reset(L);
	if(skip[R]) reset(R);
	for(int i = l; i < min(r + 1, (L + 1) * szbloco); ++i) if(dfs_array[i] == x) ++ans;
	if(L != R) for(int i = R * szbloco; i <= r; ++i) if(dfs_array[i] == x) ++ans;
	return ans;
}

int bairro;
void reroot(int u, int p = -1) {
	bairro = max(bairro, ans);
	for(int v : g[u]) {
		if(v == p) continue;
		if(k & 1) bairro = max(bairro, ans + query(l[v], r[v], k / 2 + 1));
		menos(l[v], r[v]);
		soma(0, l[v] - 1);
		soma(r[v] + 1, n - 1);
		reroot(v, u);
		soma(l[v], r[v]);
		menos(0, l[v] - 1);
		menos(r[v] + 1, n - 1);
	}
}
void solve() {
	cin >> n >> k;
	g.resize(n);
	l.resize(n);
	r.resize(n);
	h.resize(n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	h[0] = 0;
	dfs(0);
	create();
	reroot(0);
	cout << bairro << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}