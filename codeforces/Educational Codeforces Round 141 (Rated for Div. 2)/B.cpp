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
using i128 = __int128;

const int N = 50;

int a[N][N];

void solve() {
	int n;

	cin >> n;

	int l = 1, r = n * n;
	
	if(n % 2 == 0) {
		for(int i = 0, k = 0; i < n; ++i) {
			if(i % 2 == 0) {
				for(int j = 0; j < n; ++j, k ^= 1)
					a[i][j] = k == 0 ? l++ : r--;
			} else {
				for(int j = n - 1; j >= 0; --j, k ^= 1)
					a[i][j] = k == 0 ? l++ : r--;
			}
		}
	} else {
		for(int i = 0, k = 0; i < n; ++i)
			for(int j = 0; j < n; ++j, k ^= 1)
				a[i][j] = k == 0 ? l++ : r--;
	}
	
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) cout << a[i][j] << ' ';
		cout << '\n';
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
