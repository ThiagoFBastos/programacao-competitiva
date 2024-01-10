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
	
	int n, q;

	cin >> n >> q;

	vector<ii> L(n), R(n);
	int lo = 0, hi = 0;
	multiset<int> S;

	for(int i = 0; i < n; ++i) {
		int s, t, x;
		cin >> s >> t >> x;
		L[i] = {s - x, x};
		R[i] = {t - x - 1, x};
	}

	sort(L.begin(), L.end());
	sort(R.begin(), R.end());

	for(int i = 0; i < q; ++i) {
		int d;

		cin >> d;

		while(lo < n && L[lo].first <= d) {
			auto [s, x] = L[lo++];
			S.insert(x);
		}

		while(hi < n && R[hi].first < d) {
			auto [t, x] = R[hi++];
			S.erase(S.find(x));
		}
		
		if(S.empty()) cout << "-1\n";
		else cout << *S.begin() << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
