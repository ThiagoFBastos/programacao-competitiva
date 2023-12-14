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
 
const int N = 250'000 * 30;
 
int go[N][2], min_pos[N], t;
 
void add(int S, int p) {
	int i = 0;
	for(int j = 29; j >= 0; --j) {
		int c = (S >> j) & 1;
		if(go[i][c] < 0) {
			min_pos[t] = INF;
			memset(go[t], -1, sizeof go[t]);
			go[i][c] = t++;
		}
		i = go[i][c];
		min_pos[i] = min(min_pos[i], p);
	}
}
 
void solve() {
	int n, x, y = 0;
 
	cin >> n >> x;
 
	t = 1;
	min_pos[0] = INF;
	memset(go[0], -1, sizeof go[0]);
 
	ii best(-INF, -INF);
 
	for(int i = 1; i <= n; ++i) {
		int v, k = 0, pos = INF;
		add(y, i);
		cin >> v;
		y ^= v;
		for(int j = 29; j >= 0 && k >= 0; --j) {
			int c = (y >> j) & 1;
			if((x >> j) & 1) k = go[k][c^1];
			else {
				if(go[k][c^1] != -1) pos = min(pos, min_pos[go[k][c^1]]);
				k = go[k][c];
			}
		}
		if(k != -1) pos = min(pos, min_pos[k]);
		if(pos <= i) best = max(best, ii(i - pos + 1, -pos));
	}
 
	cout << -best.sc << ' ' << best.fi << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
