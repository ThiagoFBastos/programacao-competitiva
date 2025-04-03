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

const int INF = 1e7;

struct mcmf {
	int ned, n, s, t;
	vector<int> first, to, nxt, prv, cap, cost, dist, pot;

	mcmf(int _n, int _s, int _t) : n {_n}, s {_s+1}, t{_t+1} {
		ned = 0;
		first.assign(_n + 1, -1);
		prv.resize(_n + 1);
		dist.resize(_n + 1);
		pot.resize(_n + 1);
	}

	void add(int u, int v, int f, int c) {		
		++u, ++v;
		to.push_back(v);
		cap.push_back(f);
		cost.push_back(c);
		nxt.push_back(first[u]);
		first[u] = ned++;
		to.push_back(u);
		cap.push_back(0);
		cost.push_back(-c);
		nxt.push_back(first[v]);
		first[v] = ned++;
	}

	bool dijkstra() {
		fill(prv.begin(), prv.end(), -1);
		fill(dist.begin(), dist.end(), INF);
		set<ii> q;
		q.insert(ii(0, s));
		dist[s] = prv[s] = 0;
		while(!q.empty()) {
			int u = q.begin()->second;
			q.erase(q.begin());
			for(int e = first[u]; e != -1; e = nxt[e]) {
				if(cap[e] <= 0) continue ;
				int v = to[e];
				int new_dist = dist[u] + cost[e] + pot[u] - pot[v];
				if(new_dist < dist[v]) {
					q.erase(ii(dist[v], v));
					dist[v] = new_dist;
					prv[v] = e;
					q.insert(ii(new_dist, v));
				}
			}
		}
		return prv[t] != -1;
	}

	int augment(int &maxflow) {
		int flow = maxflow;

		for(int i = t; i != s; i = to[prv[i] ^ 1])
			flow = min(flow, cap[prv[i]]);

		for(int i = t; i != s; i = to[prv[i]^1]) {
			cap[prv[i]] -= flow;
			cap[prv[i]^1] += flow;
		}

		maxflow -= flow;

		int flowCost = flow * (dist[t] - pot[s] + pot[t]);

		for(int i = 1; i <= n; i++)
			if(prv[i] != -1) pot[i] += dist[i];

		return flowCost;
	}

	int mincostmaxflow(int &maxflow) {
		int flowCost = 0;
		fill(pot.begin(), pot.end(), 0);
		while(maxflow > 0 && dijkstra())
			flowCost += augment(maxflow);
		return flowCost;
	}
};
		
void solve() {
	int n, m, f = 2;

	cin >> n >> m;

	if(!n) exit(0);

	mcmf x(n + 1, 0, n);

	x.add(0, 1, 2, 0);

	while(m--) {
		int a, b, c;
		cin >> a >> b >> c;
		x.add(a, b, 1, c);
		x.add(b, a, 1, c);
	}

	int custo = x.mincostmaxflow(f);

	if(f) {
		cout << "Pernoite.\n";
		return;
	}

	cout << custo << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	//int t = 1;
	//cin >> t;
	while(true) solve();
	return 0;
}