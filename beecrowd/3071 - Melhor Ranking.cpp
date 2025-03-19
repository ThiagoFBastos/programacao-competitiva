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

int n, d, p;
vector<int> a, b;

bool position(int k) {
	for(int i = k, j = n - 1; i < n; ++i, --j) {
		if(a[i] + b[j] > p) 
			return false;
	}
	return true;
}

void solve() {

	cin >> n >> d;

	--d;

	a.resize(n);
	b.resize(n);

	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;

	p = a[d] + b[0];

	a.erase(a.begin() + d);
	b.erase(b.begin());
	--n;

	int lo = 0, hi = n;

	while(lo < hi) {
		int mid = (lo + hi) / 2;
		if(position(mid)) hi = mid;
		else lo = mid + 1;
	}

	cout << 1 + hi << '\n';
}


int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}