#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL (1ll<<62)
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

const int N = 6e3 + 10;

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


int h[N], n, b, c;;
i64 f[N], g[N];
array<i64, N> dp[2];
CHT<N, false> safe, unsafe;

void solve() {
	cin >> n >> b >> c;

	for(int i = 1; i <= n; ++i) {
		cin >> h[i];
		f[i] = f[i - 1] + h[i];
		g[i] = g[i - 1] + (i64)i * h[i];
	}

	for(int i = 0; i <= n; ++i) dp[0][i] = INFLL;
		
	for(int i = 1; i <= n; ++i) {
		i64 ans = INFLL;

		safe.clear();
		unsafe.clear();

		if(i == 1) unsafe.add(0, 0);

		for(int j = 1; j <= n; ++j) {

			safe.add(-j, dp[0][j] - g[j] + j * f[j]);

			i64 backward = safe.evaluate(f[j]) + g[j];		
	
			unsafe.add(-f[j], backward + g[j]);

			dp[1][j] = unsafe.evaluate(j) + f[j] * j - g[j];

			ans = min(ans, dp[1][j] + g[n] - g[j] - j * (f[n] - f[j]));
		}

		cout << ans * c + (i64)b * i  << ' ';		

		swap(dp[0], dp[1]);
	}

	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}