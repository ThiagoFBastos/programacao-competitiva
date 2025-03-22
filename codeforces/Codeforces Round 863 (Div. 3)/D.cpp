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

bool contains(i64 x0, i64 y0, i64 x1, i64 y1, i64 x, i64 y) {
	return x >= x0 && x <= x1 && y >= y0 && y <= y1;
}

void solve() {
	int n;
	i64 x, y;
	cin >> n >> x >> y;
	vector<i64> fib(n + 2);
	fib[0] = fib[1] = 1;
	for(int i = 2; i <= n + 1; ++i) fib[i] = fib[i - 1] + fib[i - 2];
	i64 w = fib[n + 1], h = fib[n];
	for(int i = n; i > 0; --i) {
		if(w < h) {
			swap(w, h);
			swap(x, y);
		}
		if(!contains(1, 1, fib[i], fib[i], x, y)) {
			w -= fib[i];
			y -= fib[i];
		} else if(!contains(1, w - fib[i] + 1, h, w, x, y)) {w -= fib[i];}
		else {
			cout << "NO\n";
			return;		
		}
	}
	cout << "YES\n";	
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
