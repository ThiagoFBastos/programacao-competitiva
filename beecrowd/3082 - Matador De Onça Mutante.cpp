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

const int maxn = 1e5;
int n, k, ans[maxn], a[maxn], lo[maxn], hi[maxn], ti;
vi t[maxn];

void tour(int, int);

void tour(int u, int p) {
	lo[u] = hi[u] = ti++;
	for(int v : t[u]) {
		if(v == p) continue;
		a[ti] = 1 + a[lo[u]];
		tour(v, u);
		hi[u] = max(hi[u], hi[v]);
	}
}

int c, b[maxn], res, cnt[317][maxn], cor[317];

void build();
void upd(int, int, int);
void dfs(int, int);

void build() {
	c = 1 + (int)sqrt(n);
	for(int i = 0; i < n; ++i) {
		b[i] = i / c;
		if(a[i] <= k) ++res;
		++cnt[b[i]][a[i]];
	}
}

void upd(int l, int r, int x) {
	if(l > r) return;
	int bl = b[l], br = b[r], hl, hr;
	hl = min(n, (1 + bl) * c);
	hr = min(n, (1 + br) * c);
	if(cor[bl]) {
		for(int i = bl * c; i < hl; ++i)  {
			--cnt[bl][a[i]];
			a[i] += cor[bl];
			++cnt[bl][a[i]];
		}
		cor[bl] = 0;
	}
	hl = min(hl, r + 1);
	for(int i = l; i < hl; ++i) {
		--cnt[bl][a[i]];
		if(a[i] <= k && a[i] + x > k) --res;
		else if(a[i] > k && a[i] + x <= k) ++res;
		a[i] += x;
		++cnt[bl][a[i]];
	}
	if(bl != br) {
		if(cor[br]) {
			for(int i = br * c; i < hr; ++i) {
				--cnt[br][a[i]];
				a[i] += cor[br];
				++cnt[br][a[i]];
			}
			cor[br] = 0;
		}
		for(int i = br * c; i <= r; ++i) {
			--cnt[br][a[i]];
			if(a[i] <= k && a[i] + x > k) --res;
			else if(a[i] > k && a[i] + x <= k) ++res;
			a[i] += x;
			++cnt[br][a[i]];
		}
	}
	for(++bl; bl < br; ++bl) {
		if(x == -1 && k + 1 >= cor[bl]) res += cnt[bl][k + 1 - cor[bl]];
		else if(x == 1 && k >= cor[bl]) res -= cnt[bl][k - cor[bl]];
		cor[bl] += x;
	}
}

void dfs(int u, int p) {
	ans[u] = res;
	for(int v : t[u]) {
		if(v == p) continue;
		upd(0, lo[v] - 1, 1);
		upd(hi[v] + 1, n - 1, 1);
		upd(lo[v], hi[v], -1);
		dfs(v, u); 
		upd(0, lo[v] - 1, -1);
		upd(hi[v] + 1, n - 1, -1);
		upd(lo[v], hi[v], 1);
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	k = min(n - 1, k);
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		t[a].push_back(b);
		t[b].push_back(a);
	}
	tour(0, 0);
	build();
	dfs(0, 0);
	for(int i = 0; i < n; ++i) cout << ans[i] << '\n';
	return 0;
}