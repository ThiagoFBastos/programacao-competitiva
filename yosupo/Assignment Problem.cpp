#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int MAXN = 512;
const int INF = 0x3f3f3f3f;

int n;
int pu[MAXN], pv[MAXN], cost[MAXN][MAXN];
int pairV[MAXN], way[MAXN], minv[MAXN], table[MAXN];
bool used[MAXN];

i64 hungarian() {	

	for(int i = 1, j0 = 0; i <= n; ++i) {
		pairV[0] = i;

		memset(minv, INF, sizeof minv);
		memset(used, 0, sizeof used);

		do
		{
			used[j0] = true;
			int i0 = pairV[j0], delta = INF, j1;
			for(int j = 1; j <= n; ++j) {
				if(used[j]) continue;
				int cur = cost[i0][j] - pu[i0] - pv[j];
				if(cur < minv[j]) minv[j] = cur, way[j] = j0;
				if(minv[j] < delta) delta = minv[j], j1 = j;
			}
			for(int j = 0; j <= n; ++j) {
				if(used[j]) pu[pairV[j]] += delta, pv[j] -= delta;
				else minv[j] -= delta;
			}
			j0 = j1;
		} while(pairV[j0] != 0);

		do
		{	
			int j1 = way[j0];
			pairV[j0] = pairV[j1];
			j0 = j1;
		} while(j0);
	}

	i64 ans = 0;
	for(int i = 1; i <= n; ++i) ans += cost[pairV[i]][i];
	return ans;
}

void solve() {
	cin >> n;

	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= n; ++j)
		cin >> cost[i][j];

	cout << hungarian() << '\n';
	for(int i = 1; i <= n; ++i) table[pairV[i] - 1] = i - 1;
	for(int i = 0; i < n; ++i) cout << table[i] << ' ';
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}