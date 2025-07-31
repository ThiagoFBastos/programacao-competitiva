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

struct op {
	i64 operator()(i64 a, i64 b) {
		return max(a, b);
	}
};

#define NEUTRAL 0

template<class T, class op>
struct BIT {
	vector<T> bit;

#ifdef ROLLBACK
	vector<tuple<int, T>> lastOP;
#endif

	BIT(int n) {
		bit.assign(n + 1, NEUTRAL);
	}
	
	void upd(int k, T x) {	
#ifdef ROLLBACK
		lastOP.emplace_back(k, x);
#endif
		for(++k; k < int(bit.size()); k += k & -k) bit[k] = op()(bit[k], x);
	}
	
	T query(int k) {
		T ans = NEUTRAL;
		for(++k; k > 0; k -= k & -k) ans = op()(ans, bit[k]);
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return NEUTRAL;
		return op()(query(r), -query(l - 1));
	}

#ifdef ROLLBACK
	bool rollback() {
		if(lastOP.empty()) return false;
		int k;
		T v;
		tie(k, v) = lastOP.back(); lastOP.back();
		upd(k, -v);
		return true;
	}
#endif
};

vector<int> coords;

int get(int x) {
	return lower_bound(all(coords), x) - coords.begin();
}

void solve() {
	int n;
	cin >> n;

	map<ii, i64> p;
	map<int, vector<pair<i64, i64>>> a;

	while(n--) {
		int b, f, d;
		cin >> b >> f >> d;
		coords.pb(f);
		coords.pb(b);
		p[{b, f}] += d;
	}

	for(auto [p, d] : p) a[p.fi].pb({p.sc, d});

	sort(all(coords));

	BIT<i64, op> bit(coords.size());
	
	for(auto& [_, v] : a) {
		for(auto& [x, y] : v) y += bit.query(get(x) - 1);
		for(auto& [x, y] : v) bit.upd(get(x), y);
	}

	cout << bit.query(coords.size() - 1) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}