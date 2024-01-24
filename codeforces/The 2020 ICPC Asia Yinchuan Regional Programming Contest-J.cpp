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

const int N = 1e3 + 10;

bool vis[N * N];
ii coords[N * N], delta[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int a[N][N], sides[N * N][4], deg[N * N];

void solve() {
	int n;

	cin >> n;

	for(int i = 1; i <= n * n; ++i) {
		for(int j = 0; j < 4; ++j) {
			int u;
			cin >> u;
			sides[i][j] = u;
			if(u != -1) ++deg[u];
		}
	}

	if(n == 1) {
		cout << "1\n";
		return;
	}

	for(int i = 1; i <= n * n; ++i) {
		if(deg[i] == 2 && sides[i][1] != -1 && sides[i][3] != -1) {
			queue<int> q;
			q.push(i);
			vis[i] = true;
			coords[i] = {0, 0};
			while(!q.empty()) {
				int k = q.front(); q.pop();
				auto [x, y] = coords[k];
				a[x][y] = k;
				for(int i = 0; i < 4; ++i) {
					int l = sides[k][i];
					auto [dx, dy] = delta[i];
					if(l < 0 || vis[l]) continue;
					vis[l] = true;
					coords[l] = {x + dx, y + dy};
					q.push(l);
				}
			}			
			break;
		}
	}

	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n - 1; ++j)
			cout << a[i][j] << ' ';
		cout << a[i][n - 1] << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}
 
