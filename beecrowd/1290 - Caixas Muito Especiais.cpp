#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,mmx,sse2")
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

bool encaixa(tuple<int, int, int>& c1, tuple<int, int, int>& c2) {
	return 
	(get<0>(c1) >= get<0>(c2) && get<1>(c1) >= get<1>(c2) && get<2>(c1) >= get<2>(c2)) ||
	(get<0>(c1) >= get<0>(c2) && get<1>(c1) >= get<2>(c2) && get<2>(c1) >= get<1>(c2)) ||
	(get<0>(c1) >= get<1>(c2) && get<1>(c1) >= get<0>(c2) && get<2>(c1) >= get<2>(c2)) ||
	(get<0>(c1) >= get<1>(c2) && get<1>(c1) >= get<2>(c2) && get<2>(c1) >= get<0>(c2)) ||
	(get<0>(c1) >= get<2>(c2) && get<1>(c1) >= get<0>(c2) && get<2>(c1) >= get<1>(c2)) ||
	(get<0>(c1) >= get<2>(c2) && get<1>(c1) >= get<1>(c2) && get<2>(c1) >= get<0>(c2));
}

int volume(tuple<int, int, int> c) {
	return get<0>(c) * get<1>(c) * get<2>(c);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(;;) {
		int n, m;
		tuple<int, int, int> item;
		cin >> n >> m;
		if(n == 0) break;
		cin >> get<0>(item) >> get<1>(item) >> get<2>(item);
		int v = -1;
		vector<tuple<int, int, int>> caixa;
		for(int i = 0; i < m; ++i) {
			tuple<int, int, int> c;
			cin >> get<0>(c) >> get<1>(c) >> get<2>(c);
			if(encaixa(c, item)) {
				if(get<2>(c) > get<1>(c))
					swap(get<2>(c), get<1>(c));
				if(get<2>(c) > get<0>(c))
					swap(get<2>(c), get<0>(c));
				if(get<1>(c) > get<0>(c))
					swap(get<1>(c), get<0>(c));
				caixa.push_back(c);
			}
		}
		sort(caixa.begin(), caixa.end(), [](tuple<int, int, int> c1, tuple<int, int, int> c2) {
			return make_pair(volume(c1), c1) < make_pair(volume(c2), c2);
		});
		for(int i = 0, k; i < (int)caixa.size(); i = k) {
			k = i;
			while(k < (int)caixa.size() && caixa[i] == caixa[k]) ++k;
			if(k - i >= n) {
				v = volume(caixa[i]) - volume(item);
				break;
			}
		}
		if(v < 0) cout << "impossible\n";
		else cout << v << '\n';
	}
	return 0;
}