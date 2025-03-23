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
	
	int n, q, cnt[2] = {0};
	i64 s = 0;

	cin >> n >> q;

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		s += a;
		++cnt[a & 1];
	}

	while(q--) {
		int t, x;
		cin >> t >> x;
		s += (i64)cnt[t] * x;
		if(x & 1) {
			cnt[t ^ 1] += cnt[t];
			cnt[t] = 0;
		}
		cout << s << '\n';
	}	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}
