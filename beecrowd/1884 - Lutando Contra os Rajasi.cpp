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

	const int maxn = 2000;

	int t, n, k;
	ll h;
	ii X[maxn];

	cin >> t;

	while(t--) {

		cin >> n >> h >> k;

		vii p, q;
		int i;

		for(i = 0; i < n; ++i) {
			int x, y;
			cin >> x >> y;
			(x <= y ? p : q).push_back({x, y - x}); 
		}

		sort(p.begin(), p.end());
		for(i = 0; i < (int)p.size() && h > p[i].first; ++i)
			h += p[i].second;

		k -= (int)p.size() - i;		

		i = 0;

		for(auto [x, y] : q) {
			if(h > x) {
				h += y;
				X[i++] = make_pair(x, y);
			} else {
				pair<ll, int> b {-1, -1};
				bool a = false;
				for(int j = 0; j < i; ++j) {
					if(h - X[j].second + y > X[j].first) {
						a = true;
						break;
					}
					else if(h - X[j].second > x)
						b = max(b, make_pair(h - X[j].second, X[j].first));
				}
				if(a) {
					X[i++] = make_pair(x, y);
					h += y;
				}
				else if(b.first > h) {
					int o = 0, j;
					for(j = 0; j < i; ++j) {
						if(make_pair(h - X[j].second, X[j].first) == b)
							break;
						X[o++] = X[j];
					}
					for(++j; j < i; ++j)
						X[o++] = X[j];
					h = b.first + y;
					i = o;
					X[i++] = make_pair(x, y);
					--k;
				} else
					--k;
			}
		}
		cout << (k < 0 ? "N\n" : "Y\n");
	}

	return 0;
}