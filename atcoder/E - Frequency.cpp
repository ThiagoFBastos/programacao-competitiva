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
	
	vector<i64> frq(n, 0);
	map<int, int, greater<int>> cnt, pos;

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		if(!pos.count(a)) pos[a] = i;
		++cnt[a];
	}

	while((int)cnt.size() > 1) {
		auto [x, n] = *cnt.begin();

		auto it = next(cnt.begin());
	
		pos[it->first] = min(pos[it->first], pos[x]);

		frq[pos[x]] += (x - it->first + 0ll) * n;
		
		it->second += n;

		cnt.erase(cnt.begin());
	}

	for(auto [x, y] : cnt) frq[pos[x]] += 1ll * y * x;

	for(i64 x : frq) cout << x << '\n';
}		

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
