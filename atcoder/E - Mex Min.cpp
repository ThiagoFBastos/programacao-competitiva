#include "bits/stdc++.h"

#define endl '\n'

using namespace std;

vector<int> bit;

void upd(int k, int x) {
	for(++k; k < (int)bit.size(); k += k & -k) bit[k] += x;
}

void solve() {
	int n, m;
	cin >> n >> m;
	
	vector<int> a(n), f(n, 0);
	for(int i = 0; i < n; ++i) cin >> a[i];
	
	bit.assign(n + 1, 0);
	
	for(int i = 0; i < m; ++i) if(++f[a[i]] == 1) upd(a[i], 1);
	int ans = n + 1; 
	
	for(int i = 0; i <= n - m; ++i) {
		int k = 0, cnt = 0;
		
		for(int j = 31 - __builtin_clz(n); j >= 0; --j) {
			int r = k + (1 << j);
			if(r > n || cnt + bit[r] < r) continue;
			k = r;
			cnt += bit[r];
		}
		
		ans = min(ans, k);
		
		if(i + m < n) {
			if(--f[a[i]] == 0) upd(a[i], -1);
			if(++f[a[i + m]] == 1) upd(a[i + m], 1);
		}
	}
	
	cout << ans << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}

