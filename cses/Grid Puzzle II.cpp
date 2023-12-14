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
 
template<int MAXN, int MAXM>
struct mcmf {
	int first[MAXN], to[MAXM], nxt[MAXM], prv[MAXN];
	i64 cap[MAXM], cost[MAXM], dist[MAXN], pot[MAXN];
	int ned, n;
 
	mcmf() {}
 
	mcmf(int _n) : n {_n} {
		memset(first, -1, sizeof(int) * n);
		ned = 0;
	}
 
	void add(int u, int v, i64 f, i64 c) {
		to[ned] = v, cap[ned] = f;
		cost[ned] = c, nxt[ned] = first[u];
		first[u] = ned++;
		to[ned] = u, cap[ned] = 0;
		cost[ned] = -c, nxt[ned] = first[v];
		first[v] = ned++;
	}
 
	bool dijkstra(int s, int t) {
 
		for(int i = 0; i < n; ++i) {
			prv[i] = -1;
			dist[i] = INFLL;
		}
 
		set<pair<i64, int>> q;	
 
		q.insert(make_pair(0LL, s));
		dist[s] = prv[s] = 0;
 
		while(!q.empty()) {
			int u = q.begin()->second;
			
			q.erase(q.begin());
 
			for(int e = first[u]; e != -1; e = nxt[e]) {
				if(cap[e] <= 0) continue;
				
				int v = to[e];
				i64 new_dist = dist[u] + cost[e] + pot[u] - pot[v];
				
				if(new_dist < dist[v]) {
					q.erase(make_pair(dist[v], v));
					dist[v] = new_dist;
					prv[v] = e;
					q.insert(make_pair(new_dist, v));
				}
			}
		}
 
		return prv[t] != -1;
	}
 
	i64 augment(int s, int t, i64& maxflow) {
		i64 flow = maxflow;
 
		for(int i = t; i != s; i = to[prv[i] ^ 1])
			flow = min(flow, cap[prv[i]]);
 
		for(int i = t; i != s; i = to[prv[i] ^ 1]) {
			cap[prv[i]] -= flow;
			cap[prv[i] ^ 1] += flow;
		}
 
		maxflow -= flow;
 
		i64 flowCost = flow * (dist[t] - pot[s] + pot[t]);
 
		for(int i = 0; i < n; ++i) if(prv[i] != -1) pot[i] += dist[i];
 
		return flowCost;
	}
 
	pair<i64, i64> mincostmaxflow(int s, int t) {
		i64 flowCost = 0, maxflow = INF;
		memset(pot, 0, sizeof(i64) * n);
		while(maxflow > 0 && dijkstra(s, t))
			flowCost += augment(s, t, maxflow);
		return {flowCost, INF - maxflow};	
	}
};
 
const int MAXN = 1e2 + 10, MAXM = 6e3 + 10, OFFSET = 1000; 
 
int main(int argc, char* argv[]) {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	int n;
 
	cin >> n;
 
	mcmf<MAXN, MAXM> f(2 * n + 2);
	int sum_r = 0, sum_c = 0;
 
	for(int i = 0; i < n; ++i) {
		int r;
		cin >> r;
		sum_r += r;
		f.add(2 * n, i, r, 0);
	}
 
	for(int i = 0; i < n; ++i) {
		int c;
		cin >> c;
		sum_c += c;
		f.add(i + n, 2 * n + 1, c, 0);
	}
 
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			int a;
			cin >> a;
			f.add(i, j + n, 1, OFFSET - a);
		}
	}
 
	if(sum_r != sum_c) {
		cout << "-1\n";
		return 0;
	}
 
	auto [cost, flow] = f.mincostmaxflow(2 * n, 2 * n + 1);
 
	if(flow != sum_r) {
		cout << "-1\n";
		return 0;
	}
 
	cout << flow * OFFSET - cost << '\n';
 
	vector<string> grid(n, string(n, '.'));
 
	for(int i = 0; i < n; ++i) {
		for(int e = f.first[i]; e != -1; e = f.nxt[e]) {
			int j = f.to[e];
			if(j < 2 * n && !f.cap[e]) grid[i][j - n] = 'X';
		}
	}
 
	for(string& row : grid) cout << row << '\n';
	
	return 0;
}
