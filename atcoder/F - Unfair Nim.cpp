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

	vector<i64> a(n);
	i64 q = 0, p;

	for(i64& v : a) cin >> v;
	for(int i = 2; i < n; ++i) q ^= a[i];

	p = a[0] + a[1];
	
	if((p - q) % 2) {
		cout << "-1\n";
		return;
	}

	i64 e = (p - q) / 2;

	if(q & e) {
		cout << "-1\n";
		return;
	}

	for(int i = 39; i >= 0; --i)
		if(((q >> i) & 1) && (e | (1ll<<i)) <= a[0])
			e |= 1ll << i;

	if(!e || e > a[0]) {cout << "-1\n"; return;}

	cout << a[0] - e << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
