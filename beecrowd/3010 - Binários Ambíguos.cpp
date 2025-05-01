#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;


int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	const int maxn = 1e4 + 1;
	int t, cnt[maxn];
	
	cin >> t;

	memset(cnt, 0, sizeof cnt);

	for(int k = 2; k < maxn; ++k) {
		for(int i = 1; i < 16384; ++i) {
			ll n = 0, p = 1;
			int mask = i;
			for(int j = 0; j <= 13 && mask > 0; ++j) {
				n += (mask & 1) * p;
				if(n >= maxn || p >= maxn) 
					goto fim;
				p *= k;
				mask >>= 1;
			}
			++cnt[n];
		}
		fim:;
	}

	while(t--) {
		int n;
		cin >> n;
		cout << cnt[n] << '\n';
	}

	return 0;
}