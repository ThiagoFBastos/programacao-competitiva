#include <bits/stdc++.h>
#pragma optimize ("O3")
#pragma target ("sse,sse2")
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
#define MAXN 100000
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	vii G[MAXN];
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
	cin >> n >> m;
	vector<ll> dist(n, -1);
	for(int k = 0; k < m; ++k) {
		int u, v, cost;
		cin >> u >> v >> cost;
		G[u - 1].push_back({v - 1, cost});
	}
	pq.push({0, 0});
	while(!pq.empty()) {
		auto [dv, v] = pq.top();
		pq.pop();
		if(dist[v] == -1) {
			dist[v] = dv;
			for(auto [u, du] : G[v]) {
				if(dist[u] == -1)
					pq.push({du + dv, u});
			}
		}
	}
	for(auto c : dist) cout << c << ' ';
	cout << '\n';
    return 0;
}
