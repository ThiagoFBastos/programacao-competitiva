#pragma GCC target("popcnt")

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

const int N = 1e4 + 1;

bitset<N> l, r;

void solve() {
	while(true) {
		int n;
		char _;

		cin >> n;

		if(!n) exit(0);

		cin >> _;

		r.reset();
		l.reset();

		vector<int> p(n);

		for(int& v : p) {
			cin >> v;
			r[n - v - 1] = 1;
		}

		bool ok = false;

		for(int v : p) {
			
			int a, b;

			if(2 * v < n) a = 0, b = 2 * v;
			else a = 2 * v - n + 1, b = n - 1;

			a = n - 1 - a;

			int d = abs(b - a);

			if(a > b) ok = ok || (l & (r >> d)).count();
			else ok = ok || (l & (r << d)).count();

			l[v] = 1;
			r[n - v - 1] = 0;
		}

		cout << (ok ? "no\n" : "yes\n");
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}