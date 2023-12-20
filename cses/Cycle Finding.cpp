#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 2500;
	const ll INF = 1LL << 42;
	vii G[MAXN];
	int n, m, p[MAXN], dist[MAXN];
	ll cost[MAXN];
	bool in_queue[MAXN];
	queue<int> S;
	cin >> n >> m;
	for(int i = 0; i < n; ++i){
		cost[i] = INF;
		in_queue[i] = false;
		dist[i] = p[i] = -1;
	}
	for(int i = 0; i < m; ++i){
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		G[u].push_back({v, w});
	}
	int u = -1;
	for(int w = 0; w < n; ++w) {
		if(dist[w] == -1) {
			dist[w] = p[w] = cost[w] = 0;
			in_queue[w] = true;
			S.push(w);
			while(!S.empty()) {
				int v = S.front();
				S.pop();
				in_queue[v] = false;
				if(dist[v] >= n) {
					u = v;
					break;
				}
				for(auto [u, c] : G[v]){
					if(in_queue[u]) {
						if(cost[v] + c < cost[u]) {
							dist[u] = 1 + dist[v];
							p[u] = v; 
							cost[u] = cost[v] + c;
						}
					}
					else if(!in_queue[u]){
						if(cost[v] + c < cost[u]) {
							dist[u] = 1 + dist[v];
							p[u] = v;
							in_queue[u] = true;
							cost[u] = cost[v] + c;
							S.push(u);
						}
					}
				}
			}
			if(u != -1) break;
		}
	}
	if(u == -1) cout << "NO\n";
	else {
		vi vis(n, 0);
		stack<int> Q;
		cout << "YES\n";
		while(true) {
			if(vis[u]) {
				cout << u + 1 << ' ';
				while(Q.top() != u) {
					cout << Q.top() + 1 << ' ';
					Q.pop();
				}
				cout << Q.top() + 1 << '\n';
				break;
			}
			Q.push(u);
			vis[u] = 1;
			u = p[u];
		}
	}
	return 0;
}
