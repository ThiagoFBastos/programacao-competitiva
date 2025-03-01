#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int N = 1e5 + 100;
const int MAXLG = 17;
const int MAXB = 318;

map<int, int> hsh;
int frq[N], in[N], out[N], sp[MAXLG][N], depth[N], c[N], h[N], n, q;
deque<int> pos[N];
vector<int> g[N], proc;
i64 ans[N], res[N], sum;

int lca(int u, int v) {
	if(depth[u] > depth[v]) swap(u, v);
	int d = depth[v] - depth[u];
	for(int i = 0; (1 << i) <= d; ++i) if(d & (1 << i)) v = sp[i][v];
	if(u == v) return u;
	for(int i = 31 - __builtin_clz(depth[u]); i >= 0; --i) {
		if(sp[i][u] == sp[i][v]) continue;
		u = sp[i][u];
		v = sp[i][v];
	}
	return sp[0][u];
}

void dfs(int u, int p) {
	in[u] = proc.size();
	proc.push_back(u);
	
	sp[0][u] = p;
	for(int i = 1; (1 << i) < n; ++i) sp[i][u] = sp[i - 1][sp[i - 1][u]];

	for(int v : g[u]) {
		if(v == p) continue;
		depth[v] = 1 + depth[u];
		dfs(v, u);
	}

	out[u] = proc.size();
	proc.push_back(u);
}

void upd(int i, int x, bool le) {
	int v = proc[i];
	int k = c[v];
	frq[v] += x;
	sum -= ans[k];
	if(frq[v] % 2 == 0) {
		if(le) {
			pos[k].pop_front();
			if(!pos[k].empty()) {
				int u = pos[k].front();
				ans[k] -= (h[u] - h[v]) * (h[u] - h[v] + 0ll);
			}
		} else {
			pos[k].pop_back();
			if(!pos[k].empty()) {
				int u = pos[k].back();
				ans[k] -= (h[u] - h[v]) * (h[u] - h[v] + 0ll);
			}
		}
	} else if(le) {
		if(!pos[k].empty()) {
			int u = pos[k].front();
			ans[k] += (h[u] - h[v]) * (h[u] - h[v] + 0ll);
		}
		pos[k].push_front(v);
	} else {
		if(!pos[k].empty()) {
			int u = pos[k].back();
			ans[k] += (h[u] - h[v]) * (h[u] - h[v] + 0ll);
		}
		pos[k].push_back(v);
	}
	sum += ans[k];
}

void solve() {
	cin >> n;

	for(int i = 0; i < n; ++i) {
		cin >> c[i];
		if(!hsh.count(c[i])) hsh[c[i]] = hsh.size();
		c[i] = hsh[c[i]];
	}

	for(int i = 0; i < n; ++i) cin >> h[i];
	
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs(0, 0);

	cin >> q;
	
	using TYPE = tuple<int, int, int, int>;
	vector<TYPE> Q(q);

	for(int i = 0; i < q; ++i) {
		int u, v, w;
		cin >> u >> v;
		--u, --v;
		if(in[u] > in[v]) swap(u, v);
		w = lca(u, v);
		if(u == w) Q[i] = make_tuple(in[u], in[v], i, w);
		else Q[i] = make_tuple(out[u], in[v], i, w);
	}

	sort(Q.begin(), Q.end(), [](TYPE a, TYPE b) {
		get<0>(a) /= MAXB;
		get<0>(b) /= MAXB;
		return a < b;
	});

	int lo = 0, hi = -1;

	for(auto& _ : Q) {
		int l, r, pos, x;
		
		tie(l, r, pos, x) = _;

		while(hi < r) upd(++hi, 1, false);
		while(hi > r) upd(hi--, -1, false);
		while(lo < l) upd(lo++, -1, true);
		while(lo > l) upd(--lo, 1, true);

		res[pos] = sum - ans[c[x]];
	}

	for(int i = 0; i < q; ++i) cout << res[i] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}