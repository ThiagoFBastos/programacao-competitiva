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
	int n, g = 0, ans = 0;
	
	cin >> n;

	vector<int> a(n);

	for(int& v : a) {
		cin >> v;
		g = gcd(v, g);
	}

	for(int v : a) {
		v /= g;
		while(v % 2 == 0) v /= 2, ++ans;
		while(v % 3 == 0) v /= 3, ++ans;
		if(v != 1) {
			cout << "-1\n";
			return;
		}
	}

	cout << ans << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}