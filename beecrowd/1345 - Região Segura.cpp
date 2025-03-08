#include "bits/stdc++.h"

using namespace std;

using ll = long long;
using pt = pair<int, int>;

void solve() {
	int x1, y1, x2, y2, n;
	
	cin >> x1 >> y1 >> x2 >> y2 >> n;	
	
	if(!x1 && !y1 && !x2 && !y2) exit(0);
	
	vector<pt> p(n);
	
	for(auto& [x, y] : p) cin >> x >> y;
	
	p.emplace_back(x1, y1);
	p.emplace_back(x2, y2);
	sort(p.begin(), p.end());
	
	n += 2;
	
	auto ans = make_pair(-1, -1);
	
	for(int i = 0; i < n; ++i) {
		if(i && p[i].first == p[i - 1].first) continue;
		set<int> S;
		map<int, int, greater<int>> cnt;
		
		S.insert(y1);
		S.insert(y2);
		++cnt[y2 - y1];
		
		for(int j = i; j < n; ++j) {
			auto [x, y] = p[j];
			
			if(x == p[i].first) continue;
			
			while(cnt.begin()->second == 0) cnt.erase(cnt.begin());
			
			int w = x - p[i].first, h = cnt.begin()->first;
			
			if(w > h) swap(w, h);

			ans = max(ans, make_pair(w, h));
			
			if(auto k = S.lower_bound(y); *k != y) {
				auto i = prev(k);
				--cnt[*k - *i];
				++cnt[*k - y];
				++cnt[y - *i];
				S.insert(y);
			}
		}
	}
	
	cout << ans.first << ' ' << ans.second << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
 	return 0;
}