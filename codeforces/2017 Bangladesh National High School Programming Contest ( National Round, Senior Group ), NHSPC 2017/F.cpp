#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

int tcase;

void solve() {
	
	int n, k;

	cin >> n >> k;
	
	vector<int> a(n);
	
	for(int& v : a) cin >> v;
		
	sort(a.begin(), a.end());

	int lo = 0, hi = a.back() + 1;

	while(lo < hi) {
		int mid = (lo + hi) / 2;
		i64 s = 0;	
		for(int v : a) s += min(v, mid);	
		if(s / k < mid) hi = mid;
		else lo = mid + 1;
	}

	i64 s = 0;
	for(int v : a) s += min(v, hi - 1);

	cout << "Case " << ++tcase << ": " << s / k << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
 
