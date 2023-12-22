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

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

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
	int n;
	cin >> n;
	
	vector<ii> p(n);
	
	vector<int> a;
	
	for(auto& [x, _] : p) {
		cin >> x;
		a.push_back(x);
	}
	
	for(auto& [_, y] : p) {
		cin >> y;
		a.push_back(y);
	}
	
	sort(a.begin(), a.end());
	
	for(auto& [x, y] : p) {
		x = lower_bound(a.begin(), a.end(), x) - a.begin();
		y = lower_bound(a.begin(), a.end(), y) - a.begin();
	}
	
	sort(p.begin(), p.end());
	
	BIT<i64> bit(2 * n);
	i64 pairs = 0;
	
	for(int i = 0; i < n; ++i) {
		auto [x, y] = p[i];
		bit.upd(y, 1);
		pairs += bit.query(y, 2 * n - 1);
		int lo = lower_bound(p.begin(), p.end(), make_pair(x, -1)) - p.begin();
		pairs += i - lo;
	}

	cout << pairs << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

