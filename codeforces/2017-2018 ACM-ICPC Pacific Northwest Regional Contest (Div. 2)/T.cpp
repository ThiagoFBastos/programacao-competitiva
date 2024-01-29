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

using T = tuple<int, int, int>;

void solve() {
	
	int n, m, k, s, t;

	cin >> n >> m >> k >> s >> t;

	--s, --t;

	vector<vector<T>> adj(n);
	vector<int> X;
	vector<ii> ans;

	for(int i = 0; i < m; ++i) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		--a, --b;
		adj[a].emplace_back(b, c, d);
		X.push_back(c);
	}

	sort(X.begin(), X.end());
	X.resize(unique(X.begin(), X.end()) - X.begin());

	vector<int> last(n), memo(n);

	for(int i = 0; i < (int)X.size(); ++i) {
		priority_queue<ii> pq;
		fill(last.begin(), last.end(), -1);
		fill(memo.begin(), memo.end(), -1);
		pq.emplace(k, s);
		while(!pq.empty()) {
			auto [k, s] = pq.top();
			pq.pop();
			if(last[s] != -1) continue;
			last[s] = k;
			if(s == t) break;
			for(auto [t, c, d] : adj[s]) {
				int l = max(c, X[i]), r = min(d, k);
				if(l > r || l > X[i] || r < X[i] || memo[t] >= r) continue;
				memo[t] = r;
				pq.emplace(r, t);
			}
		}
		if(last[t] != -1) ans.emplace_back(X[i], last[t]);
	}

	sort(ans.begin(), ans.end());

	int r = 0, cnt = 0;

	for(auto [x, y] : ans) {
		x = max(r + 1, x);
		cnt += max(0, y - x + 1);
		r = y;
	}

	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
