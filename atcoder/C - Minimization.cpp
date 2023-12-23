#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n, k, pos = -1;

	cin >> n >> k;

	for(int i = 1; i <= n; ++i) {
		int a;
		cin >> a;
		if(a == 1) pos = i;
	}

	int t = INT_MAX;

	for(int i = max(1, pos - k + 1); i <= pos; ++i) {
		int l = i,r=n-min(n,i+k-1)+1;
		t = min(t, 1+(l-1+k-2)/(k-1)+(r-1+k-2)/(k-1)); 
	}

	cout << t << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 
