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
	int n;

	cin >> n;

	vector<int> a(n);
	int s = 0, ans = INF;

	for(int& v : a) {
		cin >> v;
		s ^= v;
	}
	
	if(s % 2 == 0) {
		cout << "0\n";
		return;
	}

	for(int v : a) {
		int t = v % 2, cnt = 0;
		while(v % 2 == t) v /= 2, ++cnt;
		ans = min(ans, cnt);
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
