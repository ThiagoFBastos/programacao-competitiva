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

const int N = 3e3 + 10, MOD = 998244353;

int inv[N];

int add(int a, int b) {
	a += b;
	if(a >= MOD) a -= MOD;
	return a;
}

int mul(int a, int b) {
	return (i64)a * b % MOD;
}

void solve() {
	int n, m, k;

	cin >> n >> m >> k;

	inv[1] = 1;
	for(int i = 2; i <= n; ++i) inv[i] = (MOD - MOD / i + 0ll) * inv[MOD % i] % MOD;

	vector<vector<int>> adj(n);
	vector<int> c(n), sumx2(n, 0), sumx(n, 0), sump(n, 0);

	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	for(int i = 0; i < n; ++i) cin >> c[i];
	
	sump[0] = 1;
	
	int ans = 0;	

	for(int i = 0; i < k; ++i) {
		vector<int> A(n, 0), B(n, 0), C(n, 0);
		for(int u = 0; u < n; ++u) {
			int d = adj[u].size();
			for(int v : adj[u]) {
				A[v] = add(A[v], mul(sumx2[u], inv[d]));
				B[v] = add(B[v], mul(sumx[u], inv[d]));
				C[v] = add(C[v], mul(sump[u], inv[d]));
			}
		}
		for(int u = 0; u < n; ++u) {
			if(c[u] == 0) {
				A[u] = add(A[u], add(mul(B[u], 2), C[u]));
				B[u] = add(B[u], C[u]);
			} else ans = add(ans, A[u]);
		}
		swap(sumx2, A);
		swap(sumx, B);
		swap(sump, C);
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
