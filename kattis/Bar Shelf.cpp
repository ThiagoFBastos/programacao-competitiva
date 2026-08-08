#include "bits/stdc++.h"

using namespace std;

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

using ll = long long;

void solve() {
	int n;
	
	cin >> n;
	
	vector<int> p(n);
	
	for(int& x : p) cin >> x;
	
	auto a = p;
	
	sort(a.begin(), a.end());
	
	ll ans = 0;
	BIT<ll> fi_bit(n), sc_bit(n);
	
	for(int x : p) {
		int k = lower_bound(a.begin(), a.end(), 2 * x) - a.begin();
		int i = lower_bound(a.begin(), a.end(), x) - a.begin();
		ans += sc_bit.query(k, n - 1);
		sc_bit.upd(i, fi_bit.query(k, n - 1)); 
		fi_bit.upd(i, 1);
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