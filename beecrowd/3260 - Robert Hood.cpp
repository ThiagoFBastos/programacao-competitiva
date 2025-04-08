#include "bits/stdc++.h"

using namespace std;

const int maxn = 2e3 + 1, inf = 1e9;
using ii = pair<int, int>;

int lo[maxn], hi[maxn];

void solve() {
	int n, dist = 0;
	
	cin >> n;
	
	fill(lo, lo + maxn, inf);
	fill(hi, hi + maxn, -inf);
	
	vector<ii> p(n); 
	int menor = inf, maior = -inf;
	
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		menor = min(menor, x);
		maior = max(maior, x);
		p[i] = {x, y};
	}
	
	maior -= menor;
	
	for(auto [x, y] : p) {
		x -= menor;
		lo[x] = min(lo[x], y);
		hi[x] = max(hi[x], y);
	}
	
	for(int x1 = 0; x1 <= maior; ++x1) {
		if(lo[x1] == inf) continue;
		for(int x2 = 0; x2 <= maior; ++x2) {
			int x = x2 - x1, y = 0;
			if(lo[x2] == inf) continue;
			for(int k = 0; k < 2; ++k) {
				int a = k ? lo[x1] : hi[x1];
				for(int i = 0; i < 2; ++i) {
					int b = i ? lo[x2] : hi[x2];
					y = max(y, abs(a - b));
				}
			}
			dist = max(dist, x * x + y * y);
		}
	}
	
	cout << fixed << setprecision(8) << sqrt(dist) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}