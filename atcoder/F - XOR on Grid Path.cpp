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

const int N = 25;

int a[N][N], n;
vector<pair<int, i64>> go[N][N], goback[N][N];
ii delta[] = {{1, 0}, {0, 1}};

void solve() {
	cin >> n;

	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			cin >> a[i][j];

	go[1][1].pb({a[1][1],1ll});
	goback[n][n].pb({a[n][n],1ll});

	auto fix = [](auto& X) {
		sort(all(X));
		for(int k = (int)X.size() - 1; k > 0; --k) {
			if(X[k-1].fi==X[k].fi)
				X[k-1].sc += X[k].sc;
		}
		for(int k = 0; k < (int)X.size() - 1; ++k) {
			if(X[k].fi==X[k+1].fi)
				X[k+1].sc = X[k].sc;
		}
		X.resize(unique(all(X)) - X.begin());
	};

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n - i + 1; ++j) {
			fix(go[i][j]);
			fix(goback[n-i+1][n-j+1]);
			for(auto [x, y] : go[i][j]) {
				for(auto [dx, dy] : delta) {
					int z = a[i+dx][j+dy]^x;
					go[i+dx][j+dy].pb({z, y});
				}
			}
			for(auto [x, y] : goback[n-i+1][n-j+1]) {
				for(auto [dx, dy] : delta) {
					int z = a[n-i+1-dx][n-j+1-dy]^x;
					goback[n-i+1-dx][n-j+1-dy].pb({z, y});
				}
			}
		}
	}

	i64 ans = 0;

	for(int i = 1; i <= n; ++i) {
		int j = n - i + 1;
		for(auto [x, y] : go[i][j]) {
			for(auto [dx, dy] : delta) {
				auto& X = goback[i+dx][j+dy];
				auto it = lower_bound(all(X), make_pair(x, 0ll));
				if(it == X.end() || it->fi != x) continue;
				ans += it->sc * y;
			}
		}
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
