#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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
	
	int n;

	cin >> n;

	vector<int> b;
	multiset<int> s;

	for(int i = 0; i < (1<<n); ++i) {int v; cin >> v; s.insert(v);}

	b.pb(*s.rbegin());
	s.erase(s.find(*s.rbegin()));

	for(int i = 0; i < n; ++i) {
		int l = b.size();
		for(int j = 0; j < l; ++j) {
			auto it = s.lower_bound(b[j]);
			if(it == s.begin()) continue;
			--it;
			b.pb(*it);
			s.erase(it);
		}
		sort(all(b));
	}

	cout << (s.empty() ? "Yes\n" : "No\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
