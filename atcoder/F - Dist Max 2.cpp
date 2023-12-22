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
		return a + b;
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
const T BIT<T, op> :: neutral = 0;

struct event {
	int y;
	int l, r;
	int id;
	int t;
};

bool operator<(event e1, event e2) {
	if(e1.y != e2.y) return e1.y < e2.y;
	return e1.t < e2.t;
};

void solve() {
	int n;
	cin >> n;	

	vector<ii> pt(n);
	vector<int> X, Y;

	for(auto& [y, x] : pt) {
		cin >> x >> y;
		X.pb(x);
		Y.pb(y);
	}


	sort(all(pt));
	sort(all(X));
	sort(all(Y));

	int lo = 0, hi = 1e9;
	vector<int> cnt(n);
	vector<event> e(3 * n);

	auto lb = [](auto& a, int x) {
		return lower_bound(all(a), x) - a.begin();
	};

	auto ub = [](auto& a, int x) {
		return upper_bound(all(a), x) - a.begin();
	};

	while(lo < hi) {
		int m = (lo + hi) / 2;

		BIT<int, op> b(n);

		for(int i = 0; i < n; ++i) {
			auto [y, x] = pt[i];
			int l1 = lb(X, x - m);
			int r1 = ub(X, x + m);
			int l2 = lb(Y, y - m);
			int r2 = ub(Y, y + m);
			cnt[i] = r2 - l2 + r1 - l1;
			e[i] = {y, x, x, i, 1};
			e[i+n] = {y-m, x-m,x+m,i,0};
			e[i+2*n] = {y+m, x-m,x+m,i,2};
		}

		inplace_merge(e.begin(), e.begin() + n, e.begin() + 2 * n);
		inplace_merge(e.begin(), e.begin() + 2 * n, e.begin() + 3 * n);
		
		for(auto [y, l, r, id, t] : e) {
			if(t == 0) cnt[id] += b.query(lb(X, l), ub(X, r) - 1); 
			else if(t == 1) b.upd(lb(X, l), 1);
			else cnt[id] -= b.query(lb(X, l), ub(X, r) - 1); 
		}

		if(*min_element(all(cnt)) < n) lo = m + 1;
		else hi = m;
	}
	
	cout << hi << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
