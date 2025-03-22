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

void solve() {
	int n;

	cin >> n;

	multiset<int> frq;

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		frq.insert(a);
	}

	for(int k = n; k; --k) {
		auto cnt = frq;
		bool win = true;
		for(int i = 1; i <= k; ++i) {

			auto it = cnt.upper_bound(k - i + 1);

			if(it == cnt.begin()) {
				win = false;
				break;
			}

			cnt.erase(--it);
			
			if(!cnt.empty()) cnt.erase(cnt.begin());
		}

		if(win) {
			cout << k << '\n';
			return;
		}
	}

	cout << "0\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}
