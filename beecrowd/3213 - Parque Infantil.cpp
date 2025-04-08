#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

void solve() {
	int n;
	cin >> n;
	
	if(!n) exit(0);
	
	vector<long long> a(n);
	bool flag {};
	
	for(int i = 0; i < n; ++i) {
		double v;
		cin >> v;
		a[i] = 1000 * v;
	}
	
	sort(a.rbegin(), a.rend());
	
	if(n == 1) {
		cout << "NO" << endl;
		return;
	}
	
	auto s = accumulate(a.begin(), a.end(), 0LL);
	
	for(int k = 0; k < n; ++k) {
		s -= a[k];
		if(s >= a[k]) {
			flag = true;
			break;
		}
	}
	
	cout << (flag ? "YES" : "NO") << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	while(1) solve();
	return 0;
}