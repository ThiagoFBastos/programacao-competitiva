#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
//#pragma GCC target ("sse,sse2,sse3,sse4,avx,avx2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int x, y, n;
		cin >> x >> y;
		n = max(x, y);
		int x0, y0;		
		ll m = 1LL * n * n; 
		if(n & 1) {
			x0 = 1, y0 = n;
			if(y == y0)
				m -= x - x0;
			else
				m -= n - 1 + y0 - y;
		}
		else {
			x0 = n, y0 = 1;
			if(x == x0)
				m -= y - y0;
			else
				m -= n - 1 + x0 - x;
		}
	
		cout << m << '\n';
	}
	return 0;
} 
