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

const int MOD = 1e9 + 7;

int countSubs(string& s) {
	vector<int> cnt(26, 0);
	int ans = 1;
	for(char c : s) {
		int t = ans - cnt[c - 'a'];
		if(t < 0) t += MOD;
		cnt[c - 'a'] = ans;
		ans += t;
		if(ans >= MOD) ans -= MOD;
	}
	return ans;
}

void solve() {
	int n, k;
	string t;

	cin >> n >> k >> t;
	
	vector<int> last(k, -1);
	
	for(int i = 0; i < (int)t.size(); ++i) last[t[i] - 'a'] = i;

	for(int i = 0; i < n; ++i) {
		int k = min_element(all(last)) - last.begin();
		t += k + 'a';
		last[k] = t.size() + i;
	}

	cout << countSubs(t) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}