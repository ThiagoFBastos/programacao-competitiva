#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

void solve() {
	ii pt[3];
	bool flag = false;

	for(int i = 0; i < 3; ++i) cin >> pt[i].fi >> pt[i].sc;

	for(int k = 0; k < 2; ++k) {
		multiset<int> st;
		for(auto& x : pt) st.emplace(x.sc);
		for(int i = 0; i < 3; ++i) {
			st.erase(st.find(pt[i].sc));
			flag = flag || (pt[i].sc < *st.rbegin() && pt[i].sc > *st.begin());
			st.emplace(pt[i].sc);
		}
		for(auto& x : pt) swap(x.fi, x.sc);
	}

	cout << (flag ? "YES\n" : "NO\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
