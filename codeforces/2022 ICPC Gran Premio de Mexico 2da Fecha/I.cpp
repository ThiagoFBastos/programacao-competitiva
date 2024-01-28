#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T ,  null_type , less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

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

const int N = 1e5 + 10, K = 1250;

int cur[N], frq[N], big[N];
vector<int> pos[N], z;
i64 pairs[K][K];
unordered_map<i64, i64> smallp;

i64 addr(int x, int y) {
	return (i64)x * z.size() + y;
}

void solve() {
	int n, k, q;
	ordered_set<ii> os;
	i64 inv = 0;

	cin >> n >> k >> q;

	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		inv += os.size() - os.order_of_key({a + 1, -1});
		pos[a].pb(i);
		os.insert({a, i});
	}

	vector<tuple<int,int,int>> A;

	for(int i = 1; i <= k; ++i) {
		big[i] = -1;
		cur[i] = i;
		if((int)pos[i].size() > 80) {
			big[i] = z.size();
			z.pb(i);
		}
		for(int j : pos[i]) A.pb({j, i, (int)pos[i].size() > 80});
	}

	sort(all(A));

	for(auto [_, v, t] : A) {
		int k = lower_bound(all(z), v) - z.begin();
		for(int j = 0; j < (int)z.size(); ++j) {
			if(z[j] == v && t) continue;
			if(t) pairs[k][j] += frq[j];
			else smallp[addr(v, j)] += frq[j];
		}
		if(t == 1) ++frq[k];
	}

	while(q--) {
		int i;
		cin >> i;
		int& x = cur[i], &y = cur[i + 1];
		if(big[x] != -1 && big[y] != -1) {
			inv -= pairs[big[x]][big[y]];
			inv += pairs[big[y]][big[x]];
		} else if(big[x] == -1 && big[y] == -1) {
			int lo = 0;
			for(int v : pos[x]) {
				while(lo < (int)pos[y].size() && pos[y][lo] < v) ++lo;
				inv -= lo;
				inv += (int)pos[y].size() - lo;
			}
		} else if(big[y] != -1) {
			i64 t = (i64)pos[x].size() * pos[y].size();
			inv += t - 2 * smallp[addr(x, big[y])];
		} else {
			i64 t = (i64)pos[x].size() * pos[y].size();
			inv += 2 * smallp[addr(y, big[x])] - t;
		}
		cout << inv << '\n';
		swap(x, y);
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

