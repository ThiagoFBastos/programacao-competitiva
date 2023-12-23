#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

using ii = pair<int, int>;

int d[8][8];

void solve() {
	int n, m;
	cin >> n >> m;
	
	vector<int> w(n), p(n), pre(m + 1), pos(n);
	vector<ii> a(m + 1);
	int ans = INT_MAX;
	
	for(int i = 0; i < n; ++i) {
		cin >> w[i];
		p[i] = i;
	}
	
	for(int i = 1; i <= m; ++i) cin >> a[i].second >> a[i].first;
	
	pre[0] = 0;
	a[0] = {-1, 0};
	sort(a.begin(), a.end());
	
	if(a[1].first < *min_element(w.begin(), w.end())) {
		cout << "-1" << endl;
		return;
	}
	
	for(int i = 1; i <= m; ++i) pre[i] = max(pre[i - 1], a[i].second);
	
	do
	{
		for(int i = 0; i < n; ++i) {	
			int s = 0;
			for(int j = i; j < n; ++j) {
				s += w[p[j]];
				int k = upper_bound(a.begin(), a.end(), make_pair(s - 1, INT_MAX)) - a.begin() - 1;
				d[i][j] = pre[k];
			}
		}
		
		fill(pos.begin(), pos.end(), 0);
	
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
				pos[j] = max(pos[j] + 0LL, 1LL * pos[i] + d[i][j]);
	
		ans = min(ans, pos.back());
		
	} while(next_permutation(p.begin(), p.end()));
	
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

