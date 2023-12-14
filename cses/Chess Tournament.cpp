#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ordered_set tree <int ,  null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update >
using namespace std;
using namespace __gnu_pbds;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
bool possible(vii& d) {
	int p = 0, r = 0, high = d.size();
	for(int i = 0; i < d.size(); ++i) {
		while(high - 1 > i && d[high - 1].first <= i) r += d[--high].first;
		p += d[i].first;
		if(r + (i + 1LL) * (high - 1LL) < p) return false;
	}
	return (p & 1) == 0;
}
void read(int& n) {
	int ch = getchar_unlocked();
	while(ch < '0') ch = getchar_unlocked();
	n = 0;
	while(ch >= '0') {
		n = 10 * n + ch - '0';
		ch = getchar_unlocked();
	}
}
int main() {
	int n;
	read(n);
	vii d(n);
	for(int i = 0; i < n; ++i) {
		read(d[i].first);
		d[i].second = i + 1;
	}
	sort(d.rbegin(), d.rend());
	if(possible(d)) {
		vii rounds;
		for(int k = 0; k < d.size(); ++k) {
			if(d[k].first == 0) break;
			int x = d[k].first;
			for(int i = k + 1; x; ++i, --x) {
				int j = i + x - 1;
				if(j + 1 < d.size() && d[i].first == d[j + 1].first) {
					i = n - (lower_bound(d.rbegin(), d.rend(), make_pair(d[i].first, 0)) - d.rbegin());
					while(--i, x--) {
						--d[i].first;
						rounds.push_back({d[k].second, d[i].second});
					}
					break;
				}
				--d[i].first;
				rounds.push_back({d[k].second, d[i].second});
			}
		}
		printf("%u\n", rounds.size());
		for(auto [a, b] : rounds) printf("%d %d\n", a, b);
	}
	else 
		puts("IMPOSSIBLE");
	return 0;
}
