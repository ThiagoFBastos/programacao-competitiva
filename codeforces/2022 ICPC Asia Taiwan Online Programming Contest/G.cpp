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

const int N = 1e3 + 10;

array<i64, N> dp[2];

template<int N, bool maxcht>
struct CHT {

	pair<i64, i64> cht[N];
	int lo, hi;

	CHT() {clear();}

	void clear() {
		lo = hi = 0;
	}

	ld intersc(pair<i64, i64> a, pair<i64, i64> b) {
		return (b.sc - a.sc) / ld(a.fi - b.fi);
	}

	bool util(pair<i64, i64> a, pair<i64, i64> b, pair<i64, i64> c) {
		return b.fi == c.fi || intersc(b, c) < intersc(a, b);
	}

	void add(i64 a, i64 b) {
		auto fn = make_pair(a, b);
		while(lo + 2 <= hi && util(cht[hi - 2], cht[hi - 1], fn)) --hi;
		cht[hi++] = fn;
	}

	i64 evaluate(i64 x) {
		if(lo == hi) {
			if constexpr(maxcht)
				return -INFLL;
			else
				return INFLL;
		}
		while(lo + 2 <= hi) {
			i64 v1 = cht[lo].fi * x + cht[lo].sc;
			i64 v2 = cht[lo + 1].fi * x + cht[lo + 1].sc;
			if constexpr(maxcht) {
				if(v1 > v2) break;
			} else {
				if(v1 < v2) break;
			}
			++lo;
		}
		return cht[lo].fi * x + cht[lo].sc;
	}
};

CHT<N, true> cht;

void solve() {
	int n, m;
	i64 ans = -INFLL;

	cin >> n >> m;

	vector<int> a(n), b(n);

	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;
	
	for(int i = 0; i < n; ++i) {
		for(int d : {-1, 1}) {
			fill(all(dp[0]), -INFLL);
			dp[0][min(i, n - i)] = 0;
			for(int k = 0; k < n; ++k) {
				int pos = (i + k * d + n * n) % n;
				cht.clear();
				for(int j = 0; j <= m; ++j) dp[1][j] = -INFLL;
				for(int j = 0; j <= m; ++j) {
					i64 new_dp = cht.evaluate(j) + 2 * a[pos] * j - (i64)b[pos] * j * j + b[pos] * j; 
					dp[1][j + 1] = max(dp[1][j + 1], max(dp[0][j], new_dp / 2));
					ans = max(ans, new_dp / 2);
					cht.add(2ll * j * b[pos], 2 * dp[0][j] - 2ll * a[pos] * j - (i64)b[pos] * j * j - b[pos] * j);
				}
				swap(dp[0], dp[1]);
			}
		}
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

