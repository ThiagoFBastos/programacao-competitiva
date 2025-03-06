#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n;
	const int N = 250;
	bitset<N> ansID, ansValue;
	bool vis[N];

	cin >> n;

	vector<pair<bitset<N>, bitset<N>>> A(n);

	memset(vis, false, sizeof vis);
 
	for(int i = 0; i < n; ++i) {
		A[i].second[i] = 1;
		while(true) {
			int a;
			cin >> a;
			if(a < 0) break;
			A[i].first[a - 1] = 1;
		}
	}

	for(int i = n - 1, lo = 0; i >= 0; --i) {
		for(int k = lo; k < n; ++k) {
			if(A[k].first[i]) {
				swap(A[k], A[lo]);
				break;
			}
		}
		if(!A[lo].first[i]) continue;
		for(int k = ++lo; k < n; ++k) {
			if(A[k].first[i]) {
				A[k].first ^= A[lo - 1].first;
				A[k].second ^= A[lo - 1].second;
			}
		}
	}

	for(int i = 0; i < n; ++i) {
		if(ansValue.to_string() < (ansValue ^ A[i].first).to_string()) {
			ansValue ^= A[i].first;
			ansID ^= A[i].second;
		}
	}

	if((int)ansValue.count() != n) {
		cout << "No solution\n";
		return;
	}

	int m = ansID.count();
	for(int i = 0; i < n; ++i) {
		if(!ansID[i]) continue;
		cout << i + 1;
		if(--m) cout << ' ';
		else cout << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}