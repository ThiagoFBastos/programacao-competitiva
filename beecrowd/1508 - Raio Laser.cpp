#pragma GCC optimize("O3")

#include "bits/stdc++.h"

using namespace std;

const int inf = 1e9 + 1;
using ii = pair<int, int>;

void solve() {
	int n, w;
	
	cin >> n >> w;
	
	if(cin.eof() || !(n || w)) exit(0);
	
	vector<ii> p(n + 1);
	vector<int> Y(n);
	
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		p[i] = {x, y};
		Y[i] = y;
	}
	
	p.back() = make_pair(inf, 0);
	sort(p.begin(), p.end());
	sort(Y.begin(), Y.end());	
	
	int cnt = 0, x = -inf;
	
	for(int i = 0; i < n; ++i) {
		int ymin = inf, ymax = -inf;
		
		if(x == p[i].first) continue;
		
		x = p[i].first;
		
		for(int j = i; j < n; ++j) {
			if(p[j].first - p[i].first > w) break;
			
			ymin = min(ymin, p[j].second);
			ymax = max(ymax, p[j].second);
			
			if(p[j].first == p[j + 1].first) continue;
			
			++cnt;
			
			if(ymax - ymin <= w) {
				int L = lower_bound(Y.begin(), Y.end(), ymin) - Y.begin();
				int R = upper_bound(Y.begin(), Y.end(), ymax) - Y.begin();
				cnt -= R - L == j - i + 1;
			}
		}
	}
	
	int k = 0;
	Y.resize(unique(Y.begin(), Y.end()) - Y.begin());

	for(int i = 0; i < (int)Y.size(); ++i) {
		while(k < (int)Y.size() && Y[k] - Y[i] <= w) ++k;
		cnt += k - i;
	}
	
	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	for(;;) solve();
	return 0;
}