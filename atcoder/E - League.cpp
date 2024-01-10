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


void solve() {

	int n;
	
	cin >> n;

	vector<vector<int>> g(n * n);
	vector<int> deg(n * n, 0);
	int vis = 0;
	queue<ii> q;
	
	for(int i = 0; i < n; ++i) {
		vector<int> a(n - 1);
		for(int& id : a) {
			cin >> id;
			--id;
		}
		for(int k = 0; k < n - 2; ++k) {
			int from = min(i * n + a[k], a[k] * n + i);
			int to = min(i * n + a[k + 1], a[k + 1] * n + i);
			g[from].push_back(to);
			++deg[to];
		}
	}
	
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			if(deg[i * n + j] == 0)
				q.emplace(i * n + j, 0);
		}
	}
	
	int T = 0;
	while(!q.empty()) {
		auto [u, t] = q.front();
		q.pop();
		++vis;
		T = max(T, t);
		for(int v : g[u]) {
			if(--deg[v]) continue;
			q.emplace(v, t + 1);
		}
	}
	
	if(vis != n * (n - 1) / 2) {
		cout << "-1\n";
		return;
	}
	cout << T + 1 << '\n';
}

 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

