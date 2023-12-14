#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
const int N = 2e5 + 100;
 
vector<ii> adj[N];
int in[N], out[N], z[N], tms;
 
void dfs(int u) {
	in[u] = tms++;
	for(auto [v, w] : adj[u]) {
		z[v] = z[u] ^ w;
		dfs(v);
	}
	out[u] = tms - 1;
}
 
struct Node {
	int next[2];
	set<int> s;
	Node() {
		next[0] = next[1] = -1;
	}
};
 
vector<Node> t(1);
 
void push(int u) {
	int i = 0;
	for(int j = 29; j >= 0; --j) {
		int c = (z[u] >> j) & 1;
		if(t[i].next[c] < 0) {
			t[i].next[c] = t.size();
			t.emplace_back();
		}
		t[i].s.insert(in[u]);
		i = t[i].next[c];
	}
	t[i].s.insert(in[u]);
}
 
bool has_child_in(int u, int k) {
	if(k < 0) return false;
	auto& s = t[k].s;
	auto it = s.lower_bound(in[u]);
	return it != s.end() && *it <= out[u]; 
}
 
void solve() {
	int n = 1, q;
 
	cin >> q;
 
	vector<tuple<int, int, int>> query(q);
 
	for(int i = 0; i < q; ++i) {
		string type;
		int a, b;
		cin >> type >> a >> b;
		query[i] = {type == "Query", a, b};
		if(type == "Add") {
			++n;
			adj[a].emplace_back(n, b); 
		}
	}
 
	dfs(1);
 
	push(1);
 
	n = 1;
 
	for(auto [type, a, b] : query) {
		if(type == 0) {
			++n;
			push(n);
		} else {
			int ans = 0;
			for(int i = 0, j = 29; j >= 0; --j) {
				int c = (z[a] >> j) & 1;
				if(has_child_in(b, t[i].next[c ^ 1])) {
					ans ^= 1 << j;
					i = t[i].next[c ^ 1];
				} else
					i = t[i].next[c];
			}
			cout << ans << '\n';
		}
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
