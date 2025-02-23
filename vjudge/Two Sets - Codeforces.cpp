#include "bits/stdc++.h"

using namespace std;

#define INF    1000000000
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

namespace SCC {
	const int N = 4e5 + 10;
	vector<int> adj[N], st;
	int n, t, nscc, ncc, low[N], in[N], sccid[N], cc[N];

	void add(int u, int v) {
		adj[u].pb(v);
	}

	void init(int _n) {
		n = _n;
		for(int i = 0; i < n; ++i) {
			adj[i].clear();	
			in[i] = sccid[i] = -1;
		}
		st.clear();
		t = nscc = ncc = 0;
	}

	void dfs(int u) {
		st.pb(u);
		low[u] = in[u] = t++;
		cc[u] = ncc;
		for(int v : adj[u]) {
			if(in[v] == -1) {
				dfs(v);
				low[u] = min(low[u], low[v]);
			} else if(sccid[v] == -1) low[u] = min(low[u], low[v]);
		}
		if(in[u] != low[u]) return;
		while(true) {
			int v = st.back(); st.pop_back();
			sccid[v] = nscc;
			if(u == v) break;
		}
		++nscc;
	}
	
	void build() {
		for(int v = 0; v < n; ++v) {
			if(in[v] == -1) {
				dfs(v);
				++ncc;
			}
		}
	}

	int querySCC(int u) {
		return sccid[u];
	}
};

namespace TWOSAT {
	int n;

	void init(int _n) {
		n = _n;
		SCC :: init(2 * n);
	}

	void add(int a, int tpA, int b, int tpB) {
		SCC :: add(2*a+(tpA^1), 2*b+tpB);
		SCC :: add(2*b+(tpB^1), 2*a+tpA);
	}

	void build() {
		SCC :: build();
	}

	bool is_viable(vector<int>& x) {
		x.resize(n);
		for(int i = 0; i < n; ++i) {
			if(SCC :: querySCC(2*i) == SCC :: querySCC(2*i+1)) return false;
			x[i] = SCC :: querySCC(2*i+1) < SCC :: querySCC(2*i);
		}
		return true;
	}
}

void solve() {
	int n, a, b;

	cin >> n >> a >> b;

	vector<int> p(n), x;
	map<int, int> pos;
	
	for(int i = 0; i < n; ++i) {
		cin >> p[i];
		pos[p[i]] = i;
	}

	TWOSAT :: init(2 * n);

	for(int i = 0; i < n; ++i) {

		TWOSAT :: add(2 * i, 1, 2 * i + 1, 1);	
		TWOSAT :: add(2 * i, 0, 2 * i + 1, 0);

		if(a != 2 * p[i]) {
			if(pos.count(a - p[i])) {
				int j = pos[a - p[i]];
				TWOSAT :: add(2*i,0,2*j,1);
				TWOSAT :: add(2*i,1,2*j,0);
			} else
				TWOSAT :: add(2*i,0,2*i,0);
		}

		if(b != 2 * p[i]) {
			if(pos.count(b - p[i])) {
				int j = pos[b - p[i]];
				TWOSAT :: add(2*i+1,0,2*j+1,1);
				TWOSAT :: add(2*i+1,1,2*j+1,0);
			} else
				TWOSAT :: add(2*i+1,0,2*i+1,0);
		}
	}

	TWOSAT :: build();

	if(!TWOSAT :: is_viable(x)) {
		cout << "NO\n";
		return;
	}

	cout << "YES\n";
	for(int i = 0; i < n; ++i) cout << x[2*i+1] << ' ';
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}