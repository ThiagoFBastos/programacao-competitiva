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
	i64 ans = 0;
	cin >> n;
	vector<ii> a(n);
	for(int i = 0; i < n; ++i) {
		string s;
		int x = 0, sum = 0;
		cin >> s;
		for(char c : s) {
			if(c == 'X') ++x;
			else {
				ans += (c - '0') * (i64)x;
				sum += c - '0';
			}
		}
		a[i] = {sum, x};
	}
	sort(all(a), [](ii p, ii q) {
		if(p.sc == 0 || q.sc == 0) return (p.sc == 0) < (q.sc == 0);
		return p.fi * q.sc < q.fi * p.sc;
	});
	int x = 0;
	for(auto [s, y] : a) {
		ans += (i64)s * x;
		x += y;
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
