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
ll h_sum[MAXN], sum_dist[MAXN];
int ct[MAXN], n;
vi G[MAXN];
void dfs_1(int v, int h = 0) {
	h_sum[v] = h;
	ct[v] = 1;
	for(int w : G[v]) {
		if(h_sum[w] == -1) {
			dfs_1(w, h + 1);
			h_sum[v] += h_sum[w];
			ct[v] += ct[w];
		}
	}
}
void dfs_2(int v) {
	for(int w : G[v]) {
		if(sum_dist[w] == -1) {
			sum_dist[w] = sum_dist[v] + n - 2 * ct[w];
			dfs_2(w);
		}
	}
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
	for(int v = 0; v < n; ++v)
		sum_dist[v] = h_sum[v] = -1;
	dfs_1(0);
	sum_dist[0] = h_sum[0];
	dfs_2(0);
	for(int v = 0; v < n; ++v) cout << sum_dist[v] << ' ';
	cout << '\n';	
    return 0;
}
