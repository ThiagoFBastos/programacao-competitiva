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
	
	int n;
	
	cin >> n;
	
	set<int> A, B;
	
	for(int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		A.insert(v);
	}
	
	for(int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		B.insert(v);
	}

	int ans = 0;
	
	for(int i = 0; i < n; ++i) {
		if(*A.begin() > *B.begin()) {
			++ans;
			A.erase(A.begin());
			B.erase(B.begin());
		} else if(*A.rbegin() > *B.begin()) {
			auto k = A.lower_bound(*B.begin());
			auto j = prev(B.upper_bound(*k));
			A.erase(k);
			B.erase(j);
			++ans;
		} else break;
	}
	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
 	return 0;
}


