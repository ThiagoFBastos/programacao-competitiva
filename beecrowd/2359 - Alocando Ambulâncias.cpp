#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vii>;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, q;
	while(cin >> n >> m >> q) {
		vvi G(n);
		priority_queue<ii, vii, greater<ii>> pq;
		vector<int> t(n, -1);
		for(int k = 0; k < m; ++k) {
			int u, v, w;
			cin >> u >> v >> w;
			--u, --v;
			G[u].push_back({v, w});
			G[v].push_back({u, w});
		}
		while(q--) {
			int v;
			cin >> v;
			pq.push({0, v - 1});
		}
		while(!pq.empty()) {
			auto [tempo, v] = pq.top();
			pq.pop();
			if(t[v] != -1) continue;
			t[v] = tempo;
			for(auto [u, w] : G[v]) {
				if(t[u] == -1)
					pq.push({w + tempo, u});	
			}	
		}
		cout << *max_element(t.begin(), t.end()) << '\n';
	}
	return 0;
}