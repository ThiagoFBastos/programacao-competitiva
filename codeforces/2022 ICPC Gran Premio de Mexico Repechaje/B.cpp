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

int a[N][N];
bool vis[N][N];
ii delta[] = {
  {0, 1},
  {0, -1},
  {1, 0},
  {-1, 0}  
};

void solve() {
	int n, m;
  int x0, y0;
  int x1, y1;
  
  cin >> n >> m;
  cin >> x0 >> y0;
  cin >> x1 >> y1;
  
  --x0, --y0, --x1, --y1;
  
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      cin >> a[i][j];
      --a[i][j];
    }
  }
  
  auto dfs = [&](auto& self, int x, int y, int mask)->void {
    if(vis[x][y] || !(mask & (1 << a[x][y]))) return;
    vis[x][y] = true;
    for(auto [dx, dy] : delta) {
      int i = x + dx, j = y + dy;
      if(i < 0 || j < 0 || i >= n || j >= m) continue;
      self(self, i, j, mask);
    }
  };
  
  int ans = INF;
  
  for(int i = 0; i < (1 << 10); ++i) {
     for(int k = 0; k < n; ++k)
        for(int j = 0; j < m; ++j)
          vis[k][j] = false;
      dfs(dfs, x0, y0, i);
      if(vis[x1][y1]) ans = min(ans, __builtin_popcount(i));
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
