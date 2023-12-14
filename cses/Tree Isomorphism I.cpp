#pragma GCC optimize("O3")
#include "bits/stdc++.h"
using namespace std;
using vvi = vector<vector<int>>;
using vi = vector<int>;
vvi t[2];
vi h[2], p[2];
void dfs(int i, int u) {
	for(int v : t[i][u]) {
		if(v == p[i][u]) continue;
		p[i][v] = u;
		h[i][v] = 1 + h[i][u];
		dfs(i, v);
	}
}
void solve() {
	int n;
	cin >> n;
	for(int i = 0; i < 2; ++i) {
		t[i].clear();
		t[i].resize(n);
		h[i].resize(n);
		p[i].resize(n);
		h[i][0] = p[i][0] = 0;
		for(int j = 1; j < n; ++j) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			t[i][u].push_back(v);
			t[i][v].push_back(u);
		}
		dfs(i, 0);
	}
	int lv1 = 0, lv2 = 0;
	for(int i = 0; i < n; ++i) {
		lv1 = max(lv1, h[0][i]);
		lv2 = max(lv2, h[1][i]);
	}
	if(lv1 != lv2) {
		cout << "NO\n";
		return;
	}
	vvi LV1(n), LV2(n), S1(n), S2(n);
	vi v1(n), v2(n);
	for(int v = 0; v < n; ++v) {
		LV1[h[0][v]].push_back(v);
		LV2[h[1][v]].push_back(v);
	}
	for(int i = 0; i < n; ++i) {
		if(size(LV1[i]) != size(LV2[i])) {
			cout << "NO\n";
			return;
		}
	}
	for(int v : LV1[lv1]) v1[v] = 0;
	for(int v : LV2[lv2]) v2[v] = 0;
	for(int k = lv1 - 1; k >= 0; --k) {
		vector<pair<vi, int>> L, R; 
		for(int v : LV1[k]) {
			for(int u : t[0][v]) {
				if(u == p[0][v]) continue;
				S1[v].push_back(v1[u]);
			}
			sort(S1[v].begin(), S1[v].end());
			L.push_back({S1[v], v}); 
		}
		for(int v : LV2[k]) {
			for(int u : t[1][v]) {
				if(u == p[1][v]) continue;
				S2[v].push_back(v2[u]);
			}
			sort(S2[v].begin(), S2[v].end());
			R.push_back({S2[v], v});
		}
		sort(L.begin(), L.end());
		sort(R.begin(), R.end());
		for(int v = 0; v < int(size(L)); ++v) {
			if(L[v].first != R[v].first) {
				cout << "NO\n";
				return;
			}
		}
		v1[L[0].second] = v2[R[0].second] = 0;
		for(int v = 1; v < int(size(L)); ++v) {
			v1[L[v].second] = v1[L[v - 1].second] + (L[v].first != L[v - 1].first);
			v2[R[v].second] = v2[R[v - 1].second] + (R[v].first != R[v - 1].first);
		}
	}
	cout << "YES\n";
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
