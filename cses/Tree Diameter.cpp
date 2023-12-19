#include <bits/stdc++.h>
 
#define f first
#define s second
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
 
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
 
#define MAXN 200000
 
vi G[MAXN];
int n;
int diam() {
	queue<int> q;
	vi dist(n), d(n);
	for(int v = 0; v < n; ++v) {
		d[v] = G[v].size();
		if(d[v] == 1) {
			dist[v] = 0;
			q.push(v);
		}
	}
	while(!q.empty()) {
		int v = q.front();
		q.pop();
		for(int u : G[v]) {
			if(--d[u] == 1) {
				dist[u] = 1 + dist[v];
				q.push(u);
			}
		}
	}
	int D = *max_element(dist.begin(), dist.end());
	return 2 * D + count(dist.begin(), dist.end(), D) - 1;	
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int k = 1; k < n; ++k) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	cout << diam() << '\n';
    return 0;
}
