#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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

const int N = 5e5 + 10, K = 19;

int depth[N], tail[N], value[N], first[N], up[K][N], n, q;

void init() {
	first[0] = 1;
	n = 1;
}

void add(int p, int k, int x) {
	++p, ++k;
	tail[p] = n;
	first[p] = first[k];
	depth[p] = 1 + depth[k];
	value[n] = x;
	up[0][n] = tail[k];
	for(int i = 1; i < K; ++i) up[i][n] = up[i - 1][up[i - 1][n]];
	++n;
}

int pop(int p, int k) {	
	++p, ++k;
	tail[p] = tail[k];
	first[p] = 1 + first[k];
	depth[p] = depth[k];
	int d = depth[k] - first[k], v = tail[k];
	for(int i = 0; (1 << i) <= d; ++i) if(d & (1 << i)) v = up[i][v];
	return value[v]; 
}

void solve() {
	cin >> q;
	init();
	for(int i = 0; i < q; ++i) {
		int t, k, x;
		cin >> t >> k;
		if(t == 0) {
			cin >> x;
			add(i, k, x);
		} else
			cout << pop(i, k) << '\n';
	}	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}