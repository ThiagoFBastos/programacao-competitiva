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
	int n, cnt[2] = {0};
	string s;

	cin >> n >> s;

	vector<int> ans(n - 1, 0);
	int lo[2] = {-1, -1};
	
	for(int i = 0; i < n - 1; ++i) {
		++cnt[s[i] - '0'];
		lo[s[i] - '0'] = i;
		if(s[i] == '1') {
			ans[i] = 1;
			if(cnt[0]) ans[i] += lo[0] + 1;
		} else {
			ans[i] = 1;
			if(cnt[1]) ans[i] += lo[1] + 1;
		}
	}
	for(int x : ans) cout << x << ' ';
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
