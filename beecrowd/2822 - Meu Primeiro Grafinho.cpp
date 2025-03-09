#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,mmx")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;
const int maxn = 2e5;
int w[maxn], n, q;
class BIT {
	vector<pair<int, ll>> bit;
	public:
	BIT(int n) {
		bit.assign(n + 1, make_pair(0, 0LL));
	}
	void update(int k, int x, ll y) {
		while(k < (int)bit.size()) {
			bit[k].first += x;
			bit[k].second += y;
			k += k & -k;
		}
	}
	pair<int, ll> query(int k) {
		pair<int, ll> res {0, 0LL};
		while(k > 0) {
			res.first += bit[k].first;
			res.second += bit[k].second;
			k -= k & -k;
		}
		return res;
	}
	pair<int, ll> query(int L, int R) {
		if(L > R) return {0, 0LL};
		auto a = query(R);
		auto b = query(L - 1);
		a.first -= b.first;
		a.second -= b.second;
		return a;
	}
};
ll sum(int a, int b) {
	return (b - a + 1LL) * (a + b) / 2;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		map<int, int> cnt;
		ll gen = 0;
		bool change = false;
		cin >> n;
		BIT S(n);
		for(int k = 1; k <= n; ++k) {
			w[k - 1] = k;
			++cnt[k];
			S.update(k, 1, k);
		}
		gen = n <= 1 ? 0 : n / 2LL * n - sum(1, n / 2) + sum(n / 2 + 1, n - 1) - n + n / 2 + 1;
		cin >> q;
		while(q--) {
			int t;
			cin >> t;
			if(t == 2) {
				if(change) {
					change = false;
					int wmin, wmax, mid;
					wmin = cnt.begin()->first;
					wmax = cnt.rbegin()->first;
					mid = (wmin + wmax) / 2;
					auto [l, ls] = S.query(wmin, mid);
					auto [r, rs] = S.query(mid + 1, wmax);
					gen = n <= 1 || wmax == wmin ? 0 : 1LL * l * wmax - ls + rs - 1LL * r * wmin - wmax + wmin;
				}
				cout << gen << '\n';
			}
			else {
				int a, b;
				cin >> a >> b;
				--a;
				if(--cnt[w[a]] == 0) cnt.erase(w[a]);
				S.update(w[a], -1, -w[a]);
				S.update(b, 1, b);
				w[a] = b;
				++cnt[b];
				change = true;
			}
		}
	}
	return 0;
}