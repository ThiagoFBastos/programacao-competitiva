#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int INF = 1e9;

void solve() {
	
	while(true) {
		int n;

		cin >> n;

		if(!n) break;

		map<string, int> id;

		string _o, _d;
		int o, d;

		cin >> _o >> _d;

		o = id[_o] = id.size();
		d = id[_d] = id.size();

		vector<tuple<int, int, int, int>> a(n);

		for(int i = 0; i < n; ++i) {
			string lin1, lin2, word;

			cin >> lin1 >> lin2 >> word;
	
			if(!id.count(lin1)) id[lin1] = id.size();
			if(!id.count(lin2)) id[lin2] = id.size();

			a[i] = {id[lin1], id[lin2], word[0] - 'a', word.size()};						
		}

		int m = id.size();

		vector<vector<tuple<int, int, int>>> adj(m);
		vector<vector<int>> cost(m, vector<int>(27, INF));
		vector<vector<bool>> vis(m, vector<bool>(27, false));

		set<tuple<int, int, int>> q;

		for(auto [lin1, lin2, ch, len] : a) {
			adj[lin1].emplace_back(lin2, ch, len);
			adj[lin2].emplace_back(lin1, ch, len);
		}

		cost[o][26] = 0;
		q.emplace(0, o, 26);

		int ans = -1;

		while(!q.empty()) {
			auto [cst, src, ch] = *q.begin();

			q.erase(q.begin());

			if(vis[src][ch]) continue;
		
			vis[src][ch] = true;

			if(src == d) {
				ans = cst;
				break;
			}

			for(auto [dest, c, l] : adj[src]) {
				if(c == ch || cost[dest][c] <= l + cost[src][ch]) continue;
				q.erase(make_tuple(cost[dest][c], dest, c));
				cost[dest][c] = l + cost[src][ch];
				q.emplace(cost[dest][c], dest, c);
			}
		}

		if(ans < 0) cout << "impossivel\n";
		else cout << ans << '\n';
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