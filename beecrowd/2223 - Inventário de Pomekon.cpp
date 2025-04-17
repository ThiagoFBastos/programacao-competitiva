#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
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
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

const int maxn = 1e5 + 1;

ll ft[maxn];
int n, a[maxn];

static void update(int k, int x);
static ll query(int k);
static ll query(int l, int r);

void update(int k, int x) {
	while(k <= n) {
		ft[k] += x;
		k += k & -k;
	}
}

ll query(int k) {
	ll res {};
	while(k > 0) {
		res += ft[k];
		k -= k & -k;
	}
	return res;
}

ll query(int l, int r) {
	return query(r) - query(l - 1);
}

struct Query {
	int a, b, c, k;
};

bool operator<(Query q1, Query q2) {
	return q1.c < q2.c;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int q;

		cin >> n;

		memset(ft, 0, (n + 1) * sizeof(ll));

		for(int i = 0; i < n; ++i) {
			cin >> a[i];
			update(i + 1, a[i]);
		}

		vector<Query> T1, T2;
		vector<ll> res;

		cin >> q;

		while(q--) {
			int t, a, b, c;
			cin >> t >> a >> b;
			if(t == 1) {
				cin >> c;
				if(c == 0) res.push_back(query(a, b));	
				else {
					T1.push_back({a, b, c - 1, (int)res.size()});
					res.push_back(0);
				}
			}
			else
				T2.push_back({a - 1, b, (int)T2.size(), 0});
		}

		sort(T1.begin(), T1.end());

		int k = 0, i = 0;

		while(k < (int)T2.size()) {
			update(T2[k].a + 1, T2[k].b - a[T2[k].a]);
			a[T2[k].a] = T2[k].b;
			while(i < (int)T1.size() && T1[i].c == T2[k].c) {
				res[T1[i].k] = query(T1[i].a, T1[i].b);
				++i;
			}
			++k;
		}
		for(ll ans : res) cout << ans << '\n';
	}	
	return 0;
}