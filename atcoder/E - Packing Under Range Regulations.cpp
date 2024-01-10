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

	vector<ii> a(n);
	int left = 0, cur = 0;
	multiset<ii> S;
	multiset<int> L;
	bool possible = true;

	for(auto& [l, r] : a) {
		cin >> l >> r;
		L.insert(l);
	}

	sort(a.begin(), a.end());

	while(!L.empty() || !S.empty()) {

		if(left < *L.begin()) left = *L.begin();

		while(cur < n && a[cur].first <= left) {
			swap(a[cur].first, a[cur].second);
			S.insert(a[cur]);
			++cur;
		}

		if(S.begin()->first < left) {
			possible = false;
			break;
		}

		ii pp = *S.begin();
		S.erase(S.begin());
		L.erase(L.find(pp.second));

		++left;
	}

	cout << (possible ? "Yes\n" : "No\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
