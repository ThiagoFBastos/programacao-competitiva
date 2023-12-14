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
 
const int N = 2e5 + 10, K = 447, M = 25'010;
 
vector<int> adj[N];
vector<ii> Iregions[M];
int rPos[M], sub[N], myr[N], t, bigfrom[K][M], bigto[K][M];
int n, r, q;
 
void predfs(int u) {
	int in = t++;
	for(int v : adj[u]) predfs(v);
	Iregions[myr[u]].pb({in, -1});
	Iregions[myr[u]].pb({t - 1, 1});
}
 
void bigfromdfs(int big[], int cr, int n, int u) {
	big[myr[u]] += n;
	n += myr[u] == cr;
	for(int v : adj[u]) bigfromdfs(big, cr, n, v);
	n -= myr[u] == cr;
}
 
void bigtodfs(int big[], int cr, int u) {
	sub[u] = 0;
	for(int v : adj[u]) {
		bigtodfs(big, cr, v);
		sub[u] += sub[v];
	}
	big[myr[u]] += sub[u];
	sub[u] += myr[u] == cr;
}
 
void solve() {
	int bigCur = 0;
 
	cin >> n >> r >> q;
 
	cin >> myr[0];
 
	for(int i = 1; i < n; ++i) {
		int sup;
		cin >> sup >> myr[i];
		adj[sup - 1].pb(i); 
	}
 
	predfs(0);
 
	for(int i = 1; i <= r; ++i) {
		int m = Iregions[i].size() / 2;
		sort(all(Iregions[i]));
		if(1ll * m * m < n) continue;
		bigfromdfs(bigfrom[bigCur], i, 0, 0);
		bigtodfs(bigto[bigCur], i, 0);
		rPos[i] = bigCur++;
	}
 
	while(q--) {
		int r1, r2;
 
		cin >> r1 >> r2;
 
		int n_r1 = Iregions[r1].size() / 2;
		int n_r2 = Iregions[r2].size() / 2;
 
		if(1ll * n_r1 * n_r1 >= n) cout << bigfrom[rPos[r1]][r2] << endl;
		else if(1ll * n_r2 * n_r2 >= n) cout << bigto[rPos[r2]][r1] << endl;
		else {
			int i = 0, j = 0, opens = 0, pairs = 0;
 
			auto& I1 = Iregions[r1];
			auto& I2 = Iregions[r2];
 
			while(i < (int)I1.size() && j < (int)I2.size()) {
				if(I1[i] < I2[j]) opens -= I1[i++].sc;
				else pairs += I2[j++].sc == -1 ? opens : 0;
			}
			
			cout << pairs << endl;
		}
	}
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	//cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
