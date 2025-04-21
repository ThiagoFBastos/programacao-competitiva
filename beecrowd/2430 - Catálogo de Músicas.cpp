#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
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

const int maxn = 1e5;

vi G[2 * maxn + 1], bucket[2 * maxn + 1];

int sz[2 * maxn + 1], fcnt[2 * maxn + 1], lo[maxn], hi[maxn], n, t = 1;
ll fp[2 * maxn + 1];
vector<string> path;

void dfs1(int);
void dfs2(int);
void build();

void dfs1(int v) {
	fp[v] = fcnt[v] = 0;
	if(G[v].empty())
		fcnt[v] = 1;
	for(int u : G[v]) {
		dfs1(u);
		fp[v] += 1LL * fcnt[u] * (sz[u] + (G[u].size() > 0)) + fp[u];
		fcnt[v] += fcnt[u];
	}
}

ll ans, cnt, res = LLONG_MAX;

void dfs2(int v) {
	res = min(res, ans + fp[v]);
	for(int u : G[v]) {
		if(G[u].empty()) continue;
		cnt += fcnt[v] - fcnt[u];
		ans += 3 * cnt + fp[v] - (fp[u] + fcnt[u] * (sz[u] + 1LL));
		dfs2(u);
		ans -= 3 * cnt + fp[v] - (fp[u] + fcnt[u] * (sz[u] + 1LL));
		cnt -= fcnt[v] - fcnt[u];
	}
}

void build() {
	stack<ii> S;
	unordered_map<string, int> codigo;
	for(int i = 0; i < n; ++i) {
		int k = 0;
		lo[i] = 0;
		while(path[i][k] && path[i][k] != '/') ++k;
		hi[i] = k;
		string pasta(path[i].begin(), path[i].begin() + k);
		auto ptr = codigo.find(pasta);
		if(ptr == codigo.end()) {
			G[0].push_back(t);
			sz[t] = hi[i] - lo[i];
			codigo[pasta] = t++;
			bucket[t - 1].push_back(i);
		} else
			bucket[ptr->second].push_back(i);
	}
	for(int i = 1; i < t; ++i)
		for(int x : bucket[i])
			S.push({x, i});
	while(!S.empty()) {
		auto [_, cod] = S.top();
		int ti = t;
		codigo.clear();
		codigo.reserve(100);
		while(!S.empty() && S.top().second == cod) {
			auto [pos, code] = S.top();
			S.pop();
			lo[pos] = ++hi[pos];
			while(hi[pos] < (int)path[pos].size() && path[pos][hi[pos]] != '/') ++hi[pos];
			if(lo[pos] < hi[pos]) {
				string pasta(path[pos].begin() + lo[pos], path[pos].begin() + hi[pos]);
				auto ptr = codigo.find(pasta);
				if(ptr == codigo.end()) {
					G[code].push_back(t);
					sz[t] = hi[pos] - lo[pos];
					bucket[t].push_back(pos);
					codigo[pasta] = t++;
				} else
					bucket[ptr->second].push_back(pos);
			}
		}

		while(ti < t) {
			for(int pos : bucket[ti])
				S.push({pos, ti});
			++ti;
		}
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	path.resize(n);
	for(int i = 0; i < n; ++i)
		cin >> path[i];
	build();
	dfs1(0);
	dfs2(0);
	cout << res << '\n';
	return 0;
}