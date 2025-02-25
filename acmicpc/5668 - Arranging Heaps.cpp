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

const int N = 1e3 + 100;

i64 preWX[N], preW[N];
int x[N], w[N], n, k;
CHT<N, false> cht;
array<i64, N> dp[2];

void solve() {
	while(cin >> n >> k) {

		for(int i = 1; i <= n; ++i) {
			cin >> x[i] >> w[i];
			preW[i] = preW[i - 1] + w[i];
			preWX[i] = preWX[i - 1] + (i64)w[i] * x[i];
		}

		for(int i = 0; i <= n; ++i) dp[0][i] = INFLL;
		dp[0][0] = 0;

		for(int i = 1; i <= k; ++i) {
			cht.clear();
			for(int j = 0; j <= n; ++j) {
				dp[1][j] = cht.evaluate(x[j]) - preWX[j] + x[j] * preW[j];
				cht.add(-preW[j], dp[0][j] + preWX[j]); 
			}
			swap(dp[0], dp[1]);
		}

		cout << dp[0][n] << '\n';
	}	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
