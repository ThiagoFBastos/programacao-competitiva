#include "bits/stdc++.h"

#define endl '\n'

using namespace std;

void solve() {
	int n;
	
	cin >> n;
	
	vector<int> a(n + 1, 0), cnt(n + 1, 0), p;

	for(int i = 1; i <= n; ++i) cin >> a[i];
	
	for(int k = 1; k < n; ++k) {
		for(int j = k; j >= 1 && a[j] > a[j + 1]; --j) {
			p.emplace_back(j);
			++cnt[j];
			swap(a[j], a[j + 1]);
			if((int)size(p) >= n) {
				cout << "-1" << endl;
				return;
			}
		}
	}
	
	if(!is_sorted(a.begin(), a.end())) {
		cout << "-1" << endl;
		return;
	}
	   
	for(int i = 1; i < n; ++i) {
		if(cnt[i] != 1) {
			cout << "-1" << endl;
			return;
		}
	}
	
	for(int k : p) cout << k << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}

