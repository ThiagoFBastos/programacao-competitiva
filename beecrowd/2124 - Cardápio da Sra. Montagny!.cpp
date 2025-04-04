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

int caso = 1;

void solve() {
	
	int n;
	map<string, int> s;

	cin >> n;

	if(cin.eof()) exit(0);

	vector<string> a(2 * n);

	for(int i = 0; i < n; ++i) {
		for(int k = 0; k < 2; ++k) {
			string& u = a[2 * i + k];
			cin >> u;
			if(!s.count(u)) {
				s[u] = s.size();
				if(u[0] == '!') s[u.substr(1)] = s.size();
				else s["!" + u] = s.size();
			}
		}		
	}

	int m = s.size(), tms = 0, id = 0;
	vector<vector<int>> g(m);
	stack<int> st;
	vector<int> low(m), t(m, -1), scc(m, -1);

	for(int i = 0; i < n; ++i) {
		int v[4];
		for(int j = 0; j < 2; ++j) {
			string& u = a[2 * i + j];
			v[2 * j] = s[u];
			v[2 * j + 1] = u[0] == '!' ? s[u.substr(1)] : s["!" + u];
		}
		g[v[1]].push_back(v[2]);
		g[v[3]].push_back(v[0]);
	}

	function<void(int)> dfs = [&](int u) {
		low[u] = t[u] = tms++;
		st.push(u);
		for(int v : g[u]) {
			if(t[v] == -1) {
				dfs(v);
				low[u] = min(low[u], low[v]);
			} else if(scc[v] == -1) low[u] = min(low[u], low[v]);
		}
		if(low[u] == t[u]) {
			while(true) {
				int v = st.top();
				st.pop();
				scc[v] = id;
				if(u == v) break;
			}
			++id;
		}
	};

	cout << "Instancia " << caso++ << '\n';

	for(int v = 0; v < m; ++v) {
		if(t[v] == -1) dfs(v);
		if(scc[v] == scc[v ^ 1]) {
			cout << "nao\n\n";
			return;
		}
	}

	cout << "sim\n\n";
}


int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(true) solve();
 	return 0;
}