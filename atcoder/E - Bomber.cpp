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
	int h, w, m, ans {};

	cin >> h >> w >> m;

	vector<int> col(w + 1, 0);
	vector<vector<int>> row(h + 1);
	set<ii> st;

	for(int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		++col[y];
		row[x].pb(y);
	}

	for(int i = 1; i <= w; ++i) st.emplace(col[i], i);

	for(auto& r : row) {
		for(int c : r) {
			ans = max(ans, (int)r.size() + col[c] - 1);
			st.erase(ii(col[c], c));
		}
		if(!st.empty()) ans = max(ans, (int)r.size() + st.rbegin()->fi);
		for(int c : r) st.emplace(col[c], c);
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
