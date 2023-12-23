#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

int last[20], cnt[20];

void upd(int k, int x) {
	if(x & 1 << k) --cnt[k];
	--last[k];
}

void solve() {
	int n;
	cin >> n;
	
	for(int i = 0; i < 20; ++i) {
		last[i] = n - 1;
		cnt[i] = 0;
	}
		
	vector<int> x(n);
	for(int i = 0; i < n; ++i) cin >> x[i];
	long long ans = 0;
	
	for(int i = n - 1; i >= 0; --i) {
		int nxt = n - 1;
		for(int j = 0; j < 20; ++j) {
			if(x[i] & 1 << j) ++cnt[j];
			while(cnt[j] >= 2) upd(j, x[last[j]]);
			nxt = min(nxt, last[j]);
		}
		ans += nxt - i + 1;
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
s
