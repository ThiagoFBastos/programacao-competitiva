#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n, k;

	cin >> n >> k;

	vector<int> l, r {0};

	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		if(x < 0) l.push_back(-x);
		else if(x > 0) r.push_back(x);
		else --k;
	}

	l.push_back(0);
	reverse(l.begin(), l.end());
	
	int ans = INT_MAX;

	if((int)l.size()>k) ans = l[k];
	if((int)r.size()>k) ans=min(ans,r[k]);

	for(int i = 1; i < min((int)l.size(), k+1); ++i) {
		if((int)r.size() <= k - i) continue;
		ans = min(ans, 2 * l[i] + r[k - i]);
	}

	for(int i = 1; i < min((int)r.size(), k+1); ++i) {
		if((int)l.size() <= k - i) continue;
		ans = min(ans, 2 * r[i] + l[k - i]);
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
 
