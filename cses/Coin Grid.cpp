#include "bits/stdc++.h"
 
using namespace std;
 
#define INF   1000000000
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
 
struct dinic {
	int ned;
	vector<int> cap, nxt, first, to, work, dist;
 
	dinic(int n) {
		first.assign(n, -1);
		work.resize(n);
		dist.resize(n);
		ned = 0;
	}
 
	void add(int u, int v, int c) {
		to.emplace_back(v);
		cap.emplace_back(c);
		nxt.emplace_back(first[u]);
		first[u] = ned++;
 
		to.emplace_back(u);
		cap.emplace_back(0);
		nxt.emplace_back(first[v]);
		first[v] = ned++;
	}
 
	int dfs(int u, int f, int s, int t) {
		if(!f || u == t) return f;
		for(int& e = work[u]; e != -1; e = nxt[e]) {
			int v = to[e];
			if(dist[v] == dist[u] + 1 && cap[e] > 0) {
				int df = dfs(v, min(f, cap[e]), s, t);
				if(df > 0) {
					cap[e] -= df;
					cap[e ^ 1] += df;
					return df;
				}
			}
		}
		return 0;
	}
 
	bool bfs(int s, int t) {
		fill(dist.begin(), dist.end(), -1);
		dist[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int e = first[u]; e != -1; e = nxt[e]) {
				int v = to[e];
				if(dist[v] < 0 && cap[e] > 0) {
					dist[v] = dist[u] + 1;
					q.push(v);
				}
			}
		}
		return dist[t] >= 0;
	}
 
	i64 maxflow(int s, int t) {
		i64 res = 0;
		while(bfs(s, t)) {	
			copy(first.begin(), first.end(), work.begin());
			while(int f = dfs(s, INF, s, t))
				res += f;
		}
		return res;
	}
};
 
vector<int> cover(dinic& din, int n) {
	int m = 2 * n + 2;
	vector<bool> Z(m, false), vis(m, false);
	vector<int> S;
	queue<ii> q;
 
	din.maxflow(2 * n, 2 * n + 1);
 
	auto& [ned, cap, nxt, first, to, work, dist] = din;
 
	for(int i = 0; i < n; ++i) {
		bool emp = false;
		for(int e = first[i]; e != -1; e = nxt[e]) {
			int j = to[e];
			emp = emp || (j == 2 * n && cap[e]);
		}
		if(!emp) {
			vis[i] = true;
			q.emplace(i, 1);
		}
	}
 
	while(!q.empty()) {
		auto [u, t] = q.front(); q.pop();
		Z[u] = true;
		for(int e = first[u]; e != -1; e = nxt[e]) {
			int v = to[e];
			if(v >= 2 * n || vis[v] || cap[e & ~1] != t) continue;
			q.emplace(v, t ^ 1);
			vis[v] = true;
		}
	}
 
	for(int i = 0; i < n; ++i) if(!Z[i]) S.pb(i);
	for(int i = n; i < 2 * n; ++i) if(Z[i]) S.pb(i);
 
	return S;
}
 
int main(int argc, char* argv[]) {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	int n;
 
	cin >> n;
 
	dinic din(2 * n + 2);
 
	for(int i = 0; i < n; ++i) {
		string str;
		cin >> str;
		din.add(2 * n, i, 1);
		din.add(i + n, 2 * n + 1, 1);
		for(int j = 0; j < n; ++j) {
			if(str[j] == 'o')
				din.add(i, j + n, 1);
		}
	}
	
	auto S = cover(din, n);
 
	cout << S.size() << '\n';
 
	for(int x : S) cout << (x < n ? 1 : 2) << ' ' << (x < n ? x : x - n) + 1 << '\n';
	
	return 0;
}
