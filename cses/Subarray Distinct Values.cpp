#include "bits/stdc++.h"
using namespace std;
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<pair<int, int>> a(n);
	vector<int> nxt(n), marked(n + 1, 0);
	for(int i = 0; i < n; ++i) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a.begin(), a.end());
	for(int i = 0, j; i < n; i = j) {
		for(j = i; j < n && a[i].first == a[j].first; ++j);
		nxt[a[j - 1].second] = n;
		for(int k = j - 2; k >= i; --k) nxt[a[k].second] = a[k + 1].second;
		marked[a[i].second] = 1;
	}
	int cnt = 0, j = -1;
	long long ans = 0;
	for(int i = 0; i < n; ++i) {
		while(j < n && cnt <= k) cnt += marked[++j];
		ans += j - i;
		--cnt;
		marked[nxt[i]] = 1;
		if(nxt[i] < j) ++cnt;
	}
	cout << ans << '\n';
	return 0;
}
