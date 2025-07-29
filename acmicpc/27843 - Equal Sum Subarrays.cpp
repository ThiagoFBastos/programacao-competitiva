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

vector<i64> minchange(vector<i64>& a) {
	int n = a.size();
	vector<i64> ans(n, INFLL);
	vector<tuple<i64, int, int>> st;

	for(int i = 0; i < n; ++i) {
		i64 sum = 0;
		for(int j = i; j < n; ++j) {
			sum += a[j];
			st.pb({sum, i, j});
		}
	}

	sort(all(st));

	for(int t = 0; t < 2; ++t) {
		vector<int> last(n, -1);
		for(int i = 0; i < (int)st.size(); ++i) {
			auto [sum, l, r] = st[i];
			for(int k = l; k <= r; ++k) {
				int j = last[k];
				if(j < i - 1) ans[k] = min(ans[k], abs(sum - get<0>(st[i-1])));
				last[k] = i;
			}
		}
		reverse(all(st));
	}

	return ans;
}

void solve() {
	int n;
	cin >> n;
	vector<i64> a(n);	
	for(auto& v : a) cin >> v;
	for(i64 v : minchange(a)) cout << v << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}