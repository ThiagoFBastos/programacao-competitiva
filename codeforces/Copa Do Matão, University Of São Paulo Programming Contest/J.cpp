#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

vector<vector<int>> g;
int n, m, tms, cnt_scc;
vector<int> low, t, scc, cnt, S;
vector<bool> alone;
stack<int> st;

void dfs(int u) {
	low[u] = t[u] = tms++;
	st.push(u);
	for(int v : g[u]) {
		if(t[v] == -1) {
			dfs(v);
			low[u] = min(low[v], low[u]);
		} else if(scc[v] == -1) low[u] = min(low[u], low[v]);
	}
	if(low[u] == t[u]) {
		while(true) {
			int v = st.top();
			st.pop();
			++cnt[cnt_scc];
			scc[v] = cnt_scc;
			if(v == u) break;
		}
		++cnt_scc;
	}
}

void solve() {

	int ans = 0;

	cin >> n >> m;

	g.resize(n);
	low.resize(n);
	scc.assign(n, -1);
	t.assign(n, -1);
	cnt.assign(n, 0);
	S.resize(n);	
	alone.assign(n, true);

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		alone[b] = false;
	}
	
	for(int v = 0; v < n; ++v) {
		if(t[v] == -1) dfs(v);
		S[scc[v]] = v;
	}

	for(int i = 0; i < n; ++i) {
		if(!cnt[i]) break;
		if(cnt[i] > 1) ans += 2 * cnt[i] - 1;
		else if(!alone[S[i]] || !g[S[i]].empty()) ++ans;
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


