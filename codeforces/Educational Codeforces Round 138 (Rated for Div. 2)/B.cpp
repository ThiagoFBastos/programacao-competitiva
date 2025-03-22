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
	
	int n, maxn = 0;
	i64 t = 0;

	cin >> n;

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		t += a;
	}

	for(int i = 0; i < n; ++i) {
		int b;
		cin >> b;
		t += b;
		maxn = max(maxn, b);
	}	

	cout << t - maxn << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}
