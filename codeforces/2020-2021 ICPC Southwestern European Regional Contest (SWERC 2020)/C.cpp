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

using pt = pair<double, double>;

double dist(pt a, pt b) {
	a.fi -= b.fi;
	a.sc -= b.sc;
	return a.fi * a.fi + a.sc * a.sc;
}

void solve() {
	int w, h;
	int n;

	cin >> w >> h;
	cin >> n;

	vector<pt> p(n);
	vector<bool> vis(n);
	
	for(auto& [x, y] : p) cin >> x >> y;

	double lo = 0, hi = 1e9;

	while(fabs(lo - hi) > 1e-5) {
		double m = (lo + hi) / 2;
	
		queue<int> q;		
		bool ok = true;

		fill(all(vis), false);
			
		for(int i = 0; i < n; ++i) {
			if(dist(p[i], {0, 0}) <= m * m) ok = false;
			if(p[i].fi <= m || p[i].sc >= h - m) {
				vis[i] = true;
				q.push(i);
			}
		}
	
		while(!q.empty()) {
			int i = q.front(); q.pop();
			if(p[i].fi >= w - m || p[i].sc <= m) {
				ok = false;
				break;				
			}
			for(int j = 0; j < n; ++j) {
				if(!vis[j] && dist(p[i], p[j]) <= 4 * m * m) {
					vis[j] = true;
					q.push(j);
				}
			}
		}
		
		if(ok) lo = m;
		else hi = m;
	}

	cout << fixed << setprecision(9) << hi << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
