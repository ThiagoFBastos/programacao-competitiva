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
 
const int N = 2e5;
 
int n, d;
priority_queue<ii> pq[N];
vector<int> g[N];
 
void dfs(int u, int p, int h) {
	priority_queue<ii> P;
 
	for(int v : g[u]) {
		if(v == p) continue;
		dfs(v, u, h + 1);
		P.emplace(pq[v].top().first, v);
	}
 
	while((int)P.size() >= 2) {
		auto [a, b] = P.top();
		P.pop();
		if(-a - P.top().first - 2 * h >= d) {
			P.emplace(a, b);
			break;
		}
		pq[b].pop();
		if(!pq[b].empty()) P.emplace(pq[b].top().first, b);
	}
 
	if(P.empty() || -h - P.top().first >= d) pq[u].emplace(-h, u);
	
	for(int v : g[u]) {
		if(v == p) continue;
		else if(pq[u].size() < pq[v].size()) swap(pq[u], pq[v]);		
		while(!pq[v].empty()) {
			pq[u].push(pq[v].top());
			pq[v].pop();
		}
	}
}
 
void solve() {
	cin >> n >> d;
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(0, 0, 0);
	cout << pq[0].size() << '\n';	
	while(!pq[0].empty()) {
		cout << pq[0].top().second + 1 << ' ';
		pq[0].pop();
	}
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
