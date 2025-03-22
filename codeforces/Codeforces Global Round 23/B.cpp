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

	vector<int> a(n);
	int cnt[2] = {0}, ans = INF;

	for(int& v : a) {
		cin >> v;
		if(v == 0) ++cnt[v];
	}

	if(is_sorted(all(a))) ans = 0;
	
	ans = min(ans, min(n - cnt[0], cnt[0]));

	for(int i = 0; i < n - 1; ++i) {
		if(a[i] == 0) --cnt[0];
		else ++cnt[1];
		int x = cnt[1] + max(0, cnt[0] - cnt[1]);
		ans = min(ans, x);
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}
