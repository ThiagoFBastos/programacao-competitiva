#include <bits/stdc++.h>
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
const int N = 1e5 + 100;
const int B = 300;
const int INF = 1e9;
 
vector<int> g[N];
vector<ii> dp[N];
ii tmp[B];
int id[N], tms = 1, n, m, q;
 
void merge(vector<ii>& dest, vector<ii>& src) {
	int i = 0, j = 0, k = 0;
	int n = size(dest), m = size(src);
 
	while(i < n && j < m && k < B) {
		auto [du, u] = dest[i];
		auto& [dv, v] = src[j];
		
		++dv;
 
		if(id[u] == tms) {
			++i, --dv;
			continue;		
		} else if(id[v] == tms) {
			++j, --dv;
			continue;
		} else if(du > dv) {
			id[u] = tms;
			tmp[k++] = dest[i++];
		} else {
			id[v] = tms;
			tmp[k++] = src[j++];
		}
		
		--dv;
	}
	
	
	while(i < n && k < B) {
		auto [du, u] = dest[i++];
		if(id[u] == tms) continue;
		tmp[k++] = dest[i - 1];
	}
 
	while(j < m && k < B) {
		auto& [dv, v] = src[j++];
		++dv;
		if(id[v] != tms) tmp[k++] = src[j - 1];
		--dv;
	}
 
	dest.resize(k);
	for(int i = 0; i < k; ++i) dest[i] = tmp[i];
 
	++tms;
}
 
void solve() {
 
	cin >> n >> m >> q;
 
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
	}
 
	for(int i = 0; i < n; ++i) dp[i].emplace_back(0, i);
 
	for(int u = 0; u < n; ++u)
		for(int v : g[u])
			merge(dp[v], dp[u]);
	
	vector<int> dist(n);
 
	for(int i = 0; i < q; ++i) {
		int s, y, ans = -1;
 
		cin >> s >> y;
 
		--s;
 
		if(y >= B) {
 
			fill(dist.begin(), dist.end(), 0);
 
			for(int j = 0; j < y; ++j) {
				int u;	
				cin >> u;
				dist[u - 1] = -INF;
			}
 
			for(int u = 0; u <= s; ++u)
				for(int v : g[u])
					dist[v] = max(dist[v], dist[u] + 1);
			
			cout << max(-1, dist[s]) << '\n';
		} else {
 
			for(int j = 0; j < y; ++j) {
				int u;	
				cin >> u;
				id[u - 1] = tms;
			}
 
			for(auto [d, u] : dp[s]) {
				if(id[u] == tms) continue;
				ans = max(ans, d);
			}
 
			cout << ans << '\n';
			++tms;
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
