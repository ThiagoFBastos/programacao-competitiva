#pragma GCC target("popcnt")
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

const int N = 2e3 + 10, Q = 1e4 + 10;

bitset<N> in[N], out[N], safe, unsafe;
int n, m, q, T[N], ans[Q];
vector<ii> query[N];

void solve() {
	cin >> n >> m;
	
	for(int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		out[u][v] = in[v][u] = 1;
	}

	cin >> q;

	for(int i = 0; i < q; ++i) {
		int s, t;
		cin >> s >> t;
		--s, --t;
		query[s].pb({t, i});
	}

	for(int s = 0; s < n; ++s) {
		queue<int> q;
		memset(T, -1, sizeof(int) * n);
		safe.reset();
		unsafe.reset();
		safe[s] = 1;
		T[s] = s + 1;
		for(int t = 0; t < n; ++t) {
			if(t == s) continue;
			if((safe & in[t]).count()) {	
				safe[t] = 1;
				T[t] = max(t, s) + 1;
				q.push(t);
				while(!q.empty()) {
					int u = q.front(); q.pop();
					auto A = out[u] & unsafe;
					int l = A.count();
					for(int k = 0; k < l; ++k) {
						int v = A._Find_first();
						unsafe[v] = 0;
						safe[v] = 1;
						T[v] = max(t, s) + 1;
						q.push(v);
						A[v] = 0;
					}
				}
			} else unsafe[t] = 1;
		}
		for(auto [t, k] : query[s])
			ans[k] = T[t];
	}

	for(int i = 0; i < q; ++i) cout << ans[i] << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
