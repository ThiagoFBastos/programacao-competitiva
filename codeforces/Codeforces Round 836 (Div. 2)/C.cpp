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

vector<int> P(int x) {
	vector<int> d;
	for(int p = 2; p * p <= x; ++p) {
		if(x % p) continue;
		while(x % p == 0) {
			d.pb(p);
			x /= p;
		}
	}
	if(x != 1) d.pb(x);
	return d;
}

void solve() {
	int n, x;

	cin >> n >> x;

	if(n % x) {
		cout << "-1\n";
		return;
	}

	if(n == x) {
		cout << n << ' ';
		for(int i = 2; i < n; ++i) cout << i << ' ';
		cout << "1\n";
		return;
	}

	vector<int> a(n + 1, INF);
		
	auto p = P(n / x);

	sort(rall(p));

	for(int k : p) {
		a[n / k] = n;
		n /= k;
	}

	for(int i = 2; i < (int)a.size() - 1; ++i) a[i] = a[i] == INF ? i : a[i];
	a[1] = x, a.back() = 1;

	for(int i = 1; i < (int)a.size(); ++i) cout << a[i] << ' ';
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
