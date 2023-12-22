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

const int N = 2048 + 100;

int g[N], to[N][N];
bitset<N> mex, table;

void rem(int l, int r) {
	while(l <= r) table[l++] = 0;
}

void solve() {
	int n, l, r;

	cin >> n >> l >> r;

	if(l != r) {
		int x = -1, y = -1;

		for(int i = 1; i <= n; ++i) {
			if(i - 1 == n - (i + l - 1)) {
				x = i, y = l;
				break;
			}
			if(i - 1 == n - (i + l)) {
				x = i, y = l + 1;
				break;
			}
		}

		cout << "First" << endl;

		cout << x << ' ' << y << endl;

		while(true) {
			int a, b;
			cin >> a >> b;
			if(a == 0 && b == 0) break;
			else if(a == -1 && b == -1) exit(0);
			else if(a < x) cout << x + y - 1 + a << ' ' << b << endl;
			else cout << a - (x + y - 1) << ' ' << b << endl;
		}

	} else {
		for(int i = 0; i < l; ++i) g[i] = 0;

		for(int i = l; i <= n; ++i) {
			mex.reset();
			for(int j = 1; j + l - 1 <= i; ++j) {
				int x = g[j - 1] ^ g[i - (j + l - 1)];
				mex[x] = to[i][x] = 1;
			}
			while(mex[g[i]]) ++g[i];
		}

		int t = -1;

		if(g[n]) {
			t = 0;
			cout << "First" << endl;
		} else {
			t = 1;
			cout << "Second" << endl;
		}

		table.set();

		while(true) {
			if(t == 0) {
				vector<int> blocks, start;
				int lo = 1, X = 0;

				for(int i = 1; i <= n; ++i) {
					if(!table[i]) {
						if(lo != i) {
							start.pb(lo);
							blocks.pb(i - lo);
							X ^= g[i - lo];
						}
						lo = i + 1;
					}
				}

				if(lo <= n) {
					X ^= g[n - lo + 1];
					start.pb(lo);
					blocks.pb(n - lo + 1);
				}

				for(int i = 0; i < (int)blocks.size(); ++i) {
					int b = blocks[i];
					if(to[b][X ^ g[b]]) {
						for(int j = 1; j <= b; ++j) {
							int x = g[j - 1] ^ g[b - (j + l - 1)];
							if(x == (X ^ g[b])) {
								int L = j + start[i] - 1, R = j + l - 1 + start[i] - 1;
								rem(L, R);
								cout << L << ' ' << l << endl;
								break;
							}
						}
						break;
					}
				}

			} else {
				int a, b;
				cin >> a >> b;
				if(!a && !b) break;
				else if(a < 0 && b < 0) exit(0);
				rem(a, a + b - 1);
			}

			t ^= 1;
		}
	}
}	

int main() {
    ios_base :: sync_with_stdio(false);
   // cin.tie(0);
    int t = 1;
 //	cin >> t;
    while(t--) solve();
    return 0;
}


