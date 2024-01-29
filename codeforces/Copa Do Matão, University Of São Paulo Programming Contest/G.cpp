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
	int n, k;

	cin >> n >> k;

	vector<int> a(n);
	
	map<int, int> LO, HI;
	int lo = 0, hi = 0;
	i64 ans = 0;

	for(int& v : a) cin >> v;

	for(int i = 0; i < n; ++i) {
		
		++LO[a[i]];
		++HI[a[i]];

		if(HI.size() < k) continue;

		while(HI.size() >= k) {
			auto it = HI.find(a[hi]);
			if(--it->second == 0)  {
				if(HI.size() == k) {
					++it->second;
					break;
				}
				HI.erase(it);
			}
			++hi;
		}

		while(LO.size() > k) {
			auto it = LO.find(a[lo]);
			if(--it->second == 0) LO.erase(it);
			++lo;
		}

		if(HI.size() == k) ans += hi - lo + 1;

	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}


