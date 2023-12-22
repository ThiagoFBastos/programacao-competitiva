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

struct op {
	int operator()(int a, int b) {
		return min(a, b);
	}
};

template<class T, class op>
struct SegTree {
	vector<T> st;
	const T neutral = INF;

	SegTree() {}
	
	SegTree(int n) {
		st.assign(2 * n + 1, neutral);
	}
	
	SegTree(vector<T>& a) {
		int n = a.size();
		st.resize(2 * n);
		for(int k = n; k < 2 * n; ++k) st[k] = a[k - n];
		for(int k = n - 1; k > 0; --k) st[k] = op()(st[2 * k], st[2 * k + 1]);
	}
	
	void upd(int k, T x) {
		k += st.size() / 2;
		st[k] = x;
		for(k /= 2; k > 0; k /= 2) st[k] = op()(st[2 * k], st[2 * k + 1]);
	}
	
	T query(int l, int r) {
		T ans = neutral;
		int n = st.size() / 2;
		for(l += n, r += n; l <= r; l /= 2, r /= 2) {
			if(l & 1) ans = op()(ans, st[l++]);
			if(~r & 1) ans = op()(ans, st[r--]);
		}
		return ans;
	}
};

vector<int> D(vector<int>& p) {
	int n = p.size();
	SegTree<int, op> gt(n), lt(n);
	vector<int> d(n, INF);
	for(int i = 0; i < n; ++i) {
		d[i] = min(gt.query(p[i], n - 1) - p[i], lt.query(0, p[i]) + p[i]) + i;
		gt.upd(p[i], p[i] - i);
		lt.upd(p[i], -p[i] - i);
	}
	return d;
}

void solve() {
	int n;

	cin >> n;

	vector<int> p(n);

	for(int& v : p) {
		cin >> v;	
		--v;
	}

	auto d1 = D(p);
	reverse(all(p));
	auto d2 = D(p);
	for(int i = 0; i < n; ++i) cout << min(d1[i], d2[n - i - 1]) << ' ';
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

