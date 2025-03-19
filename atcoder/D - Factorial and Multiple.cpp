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

vector<pair<i64, int>> factorise(i64 X) {
	vector<pair<i64, int>> p;
	for(i64 k = 2; k * k <= X; ++k) {
		if(X % k) continue;
		int i = 0;
		while(X % k == 0) X /= k, ++i;
		p.pb({k, i});	
	}	
	if(X != 1) p.pb({X, 1});
	return p;
}

bool isDivisible(i64 n, vector<pair<i64, int>>& F) {
	for(auto [p, i] : F) {
		i64 x = n, j = 0;
		while(x >= p) j += x /= p;
		if(j < i) return false;
	}
	return true;
}

void solve() {
	
	i64 k;

	cin >> k;

	i64 lo = 1, hi = k;

	auto F = factorise(k);

	while(lo < hi) {
		i64 m = (lo + hi) / 2;
		if(isDivisible(m, F)) hi = m;
		else lo = m + 1;
	}

	cout << hi << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
