#include "bits/stdc++.h"

using namespace std;

auto sum(int a, int b) {
	return (b - a + 1LL) * (1LL * a + b) / 2;
}

void solve() {
	int n, k;
	cin >> n >> k;
	
	map<int, int, greater<int>> cnt;
	long long ans = 0;
	
	for(int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		++cnt[v];
	}
	
	while(k > 0 && cnt.begin()->first > 0) {
		pair<int, int> p = *cnt.begin();
		auto it = next(cnt.begin());
		if(k <= p.second) {
			ans += 1LL * k * p.first;
			break;
		} else if(it == cnt.end()) {
			int i = min(k / p.second, p.first);
			ans += p.second * sum(p.first - i + 1, p.first);
			k -= i * p.second;
			p.first -= i;
			cnt.erase(cnt.begin());
			cnt.insert(p);
		} else {
			int j = p.first - it->first;
			int i = min(k / p.second, j);
			ans += p.second * sum(p.first - i + 1, p.first);
			k -= i * p.second;
			p.first -= i;
			cnt.erase(cnt.begin());
			if(i == j) it->second += p.second;
			else cnt.insert(p);
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
