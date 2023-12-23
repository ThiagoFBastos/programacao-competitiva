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

const int N = 3e2 + 10;

i64 d[N][N];

void solve() {
	int n;
	vector<tuple<int, int, int>> e;
	i64 length = 0;

	cin >> n;

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			int a;
			cin >> a;
			if(i != j) e.pb({a, i, j});
			d[i][j] = i != j ? INFLL : 0;
		}
	}

	sort(all(e));

	for(auto [w, u, v] : e) {
		if(d[u][v] > w) {
			length += w;
			for(int x = 0; x < n; ++x)
				for(int y = 0; y < n; ++y)
					d[x][y] = min(d[x][y], min(d[x][u] + d[v][y], d[x][v] + d[u][y]) + w);
		} else if(d[u][v] < w) {
			cout << "-1\n";
			return;
		}
	}

	cout << length << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}

