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

i64 cuts(vector<int>& a, int max_len) {
	i64 ans = 0;
	for(int l : a) ans += (l + max_len - 1) / max_len - 1;
	return ans;
}

void solve() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n);

	for(int& x : a) cin >> x;

	int lo = 1, hi = 1e9;

	while(lo < hi) {
		int mid = (lo + hi) / 2;
		if(cuts(a, mid) <= k) hi = mid;
		else lo = mid + 1;
	}

	cout << hi << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

