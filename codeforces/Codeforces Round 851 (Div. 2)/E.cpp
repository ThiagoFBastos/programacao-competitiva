#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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

struct op {
	int operator()(int a, int b) {
		return max(a, b);
	}
};

template<class T, class op>
struct BIT {
	vector<T> bit;
	static const T neutral;

	BIT() {}

	BIT(int n) {
		bit.assign(n + 1, neutral);
	}
	
	void upd(int k, T x) {	
		for(++k; k < int(bit.size()); k += k & -k) bit[k] = op()(bit[k], x);
	}
	
	T query(int k) {
		T ans = neutral;
		for(++k; k > 0; k -= k & -k) ans = op()(ans, bit[k]);
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return neutral;
		return op()(query(r), -query(l - 1));
	}
};

template<class T, class op>
const T BIT<T, op> :: neutral = -INF;

void solve() {
	int n;

	cin >> n;

	vector<int> dp(n + 1, -INF);

	vector<i64> ps(n + 1, 0);

	for(int i = 1; i <= n; ++i) {
		cin >> ps[i];
		ps[i] += ps[i - 1];
	}

	auto coords = ps;
	sort(all(coords));

	BIT<int, op> b(n + 1);

	auto lb = [&](i64 x) {
		return lower_bound(all(coords), x) - coords.begin();
	};

	dp[0] = 0;

	for(int i = 1; i <= n; ++i) {
		dp[i] = 0;
		if(ps[i] >= 0) dp[i] = i;
		int j = lb(ps[i]);
		dp[i] = max(dp[i], i + b.query(j));
		dp[i] = max(dp[i], dp[i - 1]);
		b.upd(lb(ps[i]), -i + dp[i]);
	}

	cout << dp[n] << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
