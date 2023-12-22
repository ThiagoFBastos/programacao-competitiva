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

struct line {
	i64 m, b;
	static i64 nu, de;
	bool is_query;
	mutable function<const line*()> succ;
	line(i64 _m, i64 _b, bool iq = false) : m {_m}, b {_b}, is_query {iq} {}
	bool operator<(const line& o) const {
		if(!o.is_query) return m < o.m;
		const line *s = succ();
		if(!s) return false;
		return (b - s->b) * de < (s->m - m) * nu;
	}
};

i64 line :: nu = 0;
i64 line :: de = 0;

template<bool maxcht>
struct DynamicHull : public multiset<line> {

	bool bad(iterator y) {
		auto z = next(y);
		if(y == begin()) {
			if(z == end()) return false;
			return y->m == z->m && y->b <= z->b;
		}
		auto x = prev(y);
		if(z == end()) return y->m == x->m && y->b <= x->b;
		return (i128)(x->b - y->b) * (z->m - y->m) >= (i128)(y->b - z->b) * (y->m - x->m); 
	}

	void insert_line(i64 m, i64 b) {
		if(!maxcht) m *= -1, b *= -1;
		auto y = insert(line(m, b));
		y->succ = [=] {return next(y) == end() ? 0 : &*next(y);};
		if(bad(y)) {erase(y); return;}
		while(next(y) != end() && bad(next(y))) erase(next(y));
		while(y != begin() && bad(prev(y))) erase(prev(y));
	}

	i64 query(i64 a, i64 b) {
		if(b < 0) a *= -1, b *= -1;
		line :: nu = a;
		line :: de = b;
		auto l = lower_bound(line(0, 0, true));
		i64 y = l->m * a + l->b;
		if(!maxcht) y *= -1;
		return y;		
	}
};

void solve() {
	int n, m;

	cin >> n >> m;

	vector<int> b(n);
	DynamicHull<true> cht;

	for(int& v : b) cin >> v;

	sort(rall(b));

	for(int i = 0; i < n; ++i) cht.insert_line(i + 1, (i + 1ll) * b[i]);

	for(int i = 0; i < m; ++i) {
		int c;
		cin >> c;
		cout << cht.query(c, 1) << " \n"[i == m - 1];
	}
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
