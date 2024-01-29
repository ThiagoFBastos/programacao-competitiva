#include "bits/stdc++.h"

using namespace std;

 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	
	int n, k, lo = 0, cnt = 1;

	cin >> n >> k;

	vector<int> a(n);

	for(int& v : a) cin >> v;

	sort(a.begin(), a.end());

	for(int i = 1; i < n; ++i) {
		if(a[i] - a[lo] >= k) {
			++cnt;
			lo = i;
		}
	}

	cout << cnt << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

