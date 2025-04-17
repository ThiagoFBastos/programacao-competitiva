#include "bits/stdc++.h"
using namespace std;

template<class T>
struct BIT {
	vector<T> bit;
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	T query(int k) {
		T ans {};
		for(; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}
};

void solve() {
	int n;
	
	if(!(cin >> n)) exit(0);
	
	BIT<int> bit(n);
	auto highs = 0LL;
	
	for(int k = 1; k <= n; ++k) bit.upd(k, 1);
	
	for(int k = 0; k < n; ++k) {
		int x;
		cin >> x;
		bit.upd(x, -1);
		highs += bit.query(x + 1, n);
	}
	
	cout << highs << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
 	return 0;
}
