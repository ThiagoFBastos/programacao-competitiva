#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>; 

template<class T>
struct BIT {
	vector<T> bit;
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	T query(int k) {
		T ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}
};

void solve() {
				
	int n, q;

	cin >> n >> q;

	vector<int> a(n);
	set<ii> S;
	BIT<i64> A(n), B(n);

	function<void(int, int)> upd = [&](int i, int x) {
		auto k = S.lower_bound(make_pair(a[i], i));
		int j = -1;
		if(k != S.begin() && prev(k)->first == a[i]) j = prev(k)->second;
		A.upd(i, x * (i - j));
		B.upd(i, x * ((i - j) * (i - 1ll)));
	};

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		S.insert(make_pair(a[i], i));
		upd(i, 1);
	}

	while(q--) {
		int t, x, y;
		cin >> t >> x;
		--x;
		if(t == 1) {	
			cin >> y;
			auto k = S.upper_bound(make_pair(a[x], x));	
			auto j = S.upper_bound(make_pair(y, x));
			int z = k == S.end() || k->first != a[x] ? n : k->second;
			int w = j == S.end() || j->first != y ? n : j->second;
			upd(x, -1);
			upd(z, -1);
			upd(w, -1);
			S.erase(make_pair(a[x], x));
			S.insert(make_pair(y, x));
			a[x] = y;
			upd(x, 1);
			upd(z, 1);
			upd(w, 1);		
		} else cout << A.query(x) * x - B.query(x) << '\n';
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