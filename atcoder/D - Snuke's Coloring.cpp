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

void solve() {
	int h, w, n;

	cin >> h >> w >> n;

	map<ii, int> frq;
	set<ii> pt;
	i64 cnt[10] = {0};
 
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		++frq[{x, y}];
		for(int dx = 0; dx < 3; ++dx) {
			for(int dy = 0; dy < 3; ++dy) {
				int X = x - dx, Y = y - dy;	
				if(X <= 0 || Y <= 0 || X + 2 > h || Y + 2 > w) continue;
				pt.emplace(X, Y);
			}
		}
	}	

	cnt[0] = (h - 2ll) * (w - 2ll);
	
	for(auto [x, y] : pt) {
		int n = 0;
		for(int dx = 0; dx < 3; ++dx) {
			for(int dy = 0; dy < 3; ++dy) {
				auto it = frq.find(ii(x + dx, y + dy));
				if(it == frq.end()) continue;
				n += it->second;
			}
		}
		if(!n) continue;
		++cnt[n], --cnt[0];
	}

	for(i64 x : cnt) cout << x << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
