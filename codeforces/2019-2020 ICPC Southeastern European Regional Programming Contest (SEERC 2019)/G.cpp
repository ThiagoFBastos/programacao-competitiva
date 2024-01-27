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

const int N = 1e2 + 10;

vector<int> A[N], B[N];

void solve() {
	int n, m, h;

	cin >> n >> m >> h;

	vector<string> a(n), b(n);

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		for(int j = 0; j < m; ++j) {
			if(a[i][j] == '1') A[i].pb(j);
		}
	}

	for(int i = 0; i < n; ++i) {
		cin >> b[i];
		for(int j = 0; j < h; ++j) {
			if(b[i][j] == '1') B[i].pb(j);
		}
	}

	vector<tuple<int, int, int>> c1, c2;

	for(int x = 0; x < n; ++x) {
		if(A[x].empty() ^ B[x].empty()) {
			cout << "-1\n";
			return;
		}
		for(int k = 0; k < (int)A[x].size(); ++k) {
			for(int j = 0; j < (int)B[x].size(); ++j) {
				int y = A[x][k];
				int z = B[x][j];
				c1.pb({x, y, z});
			}
		}
		if(A[x].size() < B[x].size()) {
			int extra = B[x].size() - A[x].size() + 1;
			for(int j = 0; j < extra; ++j) {
				int y = A[x][0];
				int z = B[x][j];
				c2.pb({x, y, z});
			}
			for(int j = extra; j < (int)B[x].size(); ++j) {
				int y = A[x][j - extra + 1];
				int z = B[x][j];
				c2.pb({x, y, z});
			}
		} else if(A[x].size() > B[x].size()) {
			int extra = A[x].size() - B[x].size() + 1;
			for(int j = 0; j < extra; ++j) {
				int y = A[x][j];
				int z = B[x][0];
				c2.pb({x, y, z});
			}
			for(int j = extra; j < (int)A[x].size(); ++j) {
				int y = A[x][j];
				int z = B[x][j - extra + 1];
				c2.pb({x, y, z});
			}
		} else {
			for(int j = 0; j < (int)A[x].size(); ++j) {
				int y = A[x][j];
				int z = B[x][j];
				c2.pb({x, y, z});
			}
		}	
	}
	
	sort(all(c1));
	sort(all(c2));

	cout << c1.size() << '\n';
	for(auto [x, y, z] : c1) cout << x << ' ' << y << ' ' << z << '\n';
	cout << c2.size() << '\n';
	for(auto [x, y, z] : c2) cout << x << ' ' << y << ' ' << z << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
