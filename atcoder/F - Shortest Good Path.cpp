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

const int N = 1 << 17;

bool vis[N], vis_path[N][17];
int cnt[N][17];

void solve() {
	int n, m, ans = 0;

	cin >> n >> m;

	vector<int> g(n, 0);

	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u] |= 1 << v;
		g[v] |= 1 << u;
	}

	queue<ii> q;

	vis[0] = true;

	for(int i = 0; i < n; ++i) {
		cnt[1 << i][i] = 1;
		vis[1 << i] = vis_path[1 << i][i] = true;
		q.emplace(1 << i, i);
		++ans;
	}

	while(!q.empty()) {
		auto [mask, u] = q.front();
		q.pop();
		for(int S = g[u]; S; S -= S & -S) {
			int v = __builtin_ctz(S);
			int T = mask ^ (1 << v);

			if(vis_path[T][v]) continue;

			cnt[T][v] = 1 + cnt[mask][u];
			vis_path[T][v] = true;

			if(!vis[T]) {
				vis[T] = true;
				ans += cnt[T][v];
			}
			
			q.emplace(T, v);
		}
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
