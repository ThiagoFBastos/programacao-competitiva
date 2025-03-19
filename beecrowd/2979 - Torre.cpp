#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

const int maxn = 5e3 + 1, mod = 1e6;

int pc[maxn], pr[maxn], n, m;
bool ocupado[maxn][maxn];

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	for(int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		ocupado[x][y] = true;
	}

	pc[1] = pr[1] = 1;
	int dp = 1;

	for(int y = 2; y <= n; ++y) {
		if(ocupado[1][y]) break;
		pr[y] = pc[y - 1];
		pc[y] = pc[y - 1] << 1;
		if(pc[y] >= mod) pc[y] -= mod;
	}
	
	for(int x = 2; x <= n; ++x) {
		for(int y = 1; y <= n; ++y) {
			if(ocupado[x][y]) {
				dp = pr[y] = pc[y] = 0;
				continue;
			}
			dp = pr[y] + pc[y - 1];
			if(dp >= mod) dp -= mod;
			pr[y] += dp;
			pc[y] = pc[y - 1] + dp;
			if(pr[y] >= mod) pr[y] -= mod;
			if(pc[y] >= mod) pc[y] -= mod;
		}
	}

	cout << dp;

	return 0;
}