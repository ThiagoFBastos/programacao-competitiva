#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n, q, x;

	cin >> n >> q >> x;

	vector<i64> w(3 * n + 1, 0);
	vector<i64> path, cycle, st;
	vector<int> vis(n, -1);
	int tms = 0;

	for(int i = 1; i <= n; ++i) {
		cin >> w[i];
		w[i + n] = w[i + 2 * n] = w[i];
	}		
	
	for(int i = 1; i <= 3 * n; ++i) w[i] += w[i - 1];

	int i = 0;
	
	while(vis[i] < 0) {
		int y = x % w[n];
		i64 cnt = (i64)x / w[n] * n;
		int k = lower_bound(w.begin(), w.end(), w[i] + y) - w.begin();
		cnt += k - i;
		st.push_back(cnt);
		vis[i] = tms++;
		i = k % n;
	}

	for(int k = 0; k < vis[i]; ++k) path.push_back(st[k]);
	for(int k = vis[i]; k < (int)size(st); ++k) cycle.push_back(st[k]);

	while(q--) {
		i64 k;
		cin >> k;
		if(k <= (int)path.size()) cout << path[k - 1] << '\n';
		else {
			k -= path.size();
			cout << cycle[(k - 1) % (int)size(cycle)] << '\n';
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
