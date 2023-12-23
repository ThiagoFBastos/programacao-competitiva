#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

const int inf = 1e9 + 1;

int n, k, q;
vector<int> a;

bool can_solve(int l, int r) {
	int cnt = 0, x = 0, y = 0;
	for(int i = 0; i < n; ++i) {
		if(a[i] < l) x = y = 0;
		else if(a[i] > r) ++y;
		else ++x;
		if(x && x + y >= k) --x, ++cnt;
	}
	return cnt >= q;
}

void solve() {
	cin >> n >> k >> q;
	
	a.resize(n);

	for(int& v : a) cin >> v;
	
	int ans = inf;
	
	auto p = a;
	sort(p.begin(), p.end());
	
	for(int i = 0; i < n; ++i) {
		int L = i, R = n - 1;
		
		if(!can_solve(p[i], p[n - 1])) continue;
		
		while(L < R) {
			int mid = (L + R) / 2;
			if(can_solve(p[i], p[mid])) R = mid;
			else L = mid + 1;
		}
		
		ans = min(ans, p[R] - p[i]);
	}
	
	cout << ans << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

