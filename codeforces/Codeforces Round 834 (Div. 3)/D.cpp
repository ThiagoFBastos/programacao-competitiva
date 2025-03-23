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
	int n, m;

	cin >> n >> m;

	int _2 = 0, _5 = 0;

	while(n % 2 == 0) n /= 2, ++_2;
	while(n % 5 == 0) n /= 5, ++_5;

	int _10 = min(_2, _5);

	_2 -= _10;
	_5 -= _10;
		
	auto ans = make_pair(0ll, 0ll);
	i64 P2 = 1;

	for(int k = 0; k <= 32; ++k) {
		i64 P5 = 1;
		for(int j = 0; j <= 32; ++j) {
			i64 i = m / ((__int128)P2 * P5);
			if(!i) break;
			ans = max(ans, make_pair(min(k + _2, j + _5) + 0ll, i64((__int128)P2 * P5 * i)));
			P5 *= 5;
		}
		P2 <<= 1;
	}

	while(_2-- > 0) n <<= 1;
	while(_5-- > 0) n *= 5;
	while(_10-- > 0) n *= 10;

	cout << n * ans.sc << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}


