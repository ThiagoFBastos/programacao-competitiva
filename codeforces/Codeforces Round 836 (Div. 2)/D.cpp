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

i64 sum(int l, int r) {
	return (l + r) * (r - l + 1ll) / 2;
}

void solve() {
	int n;

	cin >> n;

	if(n == 2) {
		cout << "1 3\n";
		return;
	}

	i64 s = (n + 1ll) * (n + 1ll);

	for(int i = 1; i <= 10 * n; ++i) {
		int x = i + n + 1;

		i64 lo = i + x + sum(i + 1, i + n - 2);
		i64 hi = i + x + sum(x - n + 2, x - 1);

		if(lo <= s && hi >= s) {
			int f = n - 2;
			cout << i << ' ' << x << ' ';
			s -= i + x;
			for(int j = i + 1; f > 0; ++j) {
				i64 lo = j + sum(j + 1, j + f - 1);
				i64 hi = j + sum(x - f + 1, x - 1);		
				if(lo <= s && hi >= s) {
					--f;
					cout << j << ' ';
					s -= j;
				}
			}
			cout << '\n';
			break;
		}
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
