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

const int N = 1501;

int H[N][N], V[N][N];

void solve() {
	int h, w, n, m;
	
	cin >> h >> w >> n >> m;
	
	vector<ii> p(n);
	
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		H[x][y] = V[x][y] = 1;
		p[i] = {x, y};
	}
	
	for(int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		H[x][y] = V[x][y] = 2;
	}
	
	for(auto [x, y] : p) {
		for(int i = x - 1; i; --i) {
			if(V[i][y]) break;
			V[i][y] = 1;
		}
		for(int i = x + 1; i <= h; ++i) {
			if(V[i][y]) break;
			V[i][y] = 1;
		}
	}
	
	for(auto [x, y] : p) {
		for(int i = y - 1; i; --i) {
			if(H[x][i]) break;
			H[x][i] = 1;
		}
		for(int i = y + 1; i <= w; ++i) {
			if(H[x][i]) break;
			H[x][i] = 1;
		}
	}
	
	int ans = 0;
	
	for(int x = 1; x <= h; ++x)
	for(int y = 1; y <= w; ++y)
		ans += H[x][y] == 1 || V[x][y] == 1;
		
	cout << ans << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
   // cin >> t;
    while(t--) solve();
    return 0;
}
