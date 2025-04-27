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

#define x first
#define y second

const int maxn = 1e3 + 3, mod = 1e9 + 7;

int C[maxn][maxn], ans[maxn], n;
ii dp[maxn];
vii p, cnt;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	p.resize(n);		
	for(int i = 0; i < n; ++i)
		cin >> p[i].x >> p[i].y;
	sort(p.begin(), p.end());
	cnt.reserve(n * n);
	for(int i = 0; i < n; ++i)
		for(int k = i + 1; k < n; ++k)
			cnt.push_back({p[i].x + p[k].x, p[i].y + p[k].y});
	sort(cnt.begin(), cnt.end());
	for(int i = 0; i <= n; ++i) {
		C[i][0] = C[i][i] = 1;
		for(int k = 1; k < n; ++k) {
			C[i][k] = C[i - 1][k] + C[i - 1][k - 1];
			if(C[i][k] >= mod) C[i][k] -= mod;
		}
	}
	for(int i = 0; i < n; ++i) 
		ans[1] = n;
	int lo = 0;
	for(int i = 0, k; i < (int)cnt.size(); i = k) {
		k = i;
		while(k < (int)cnt.size() && cnt[k] == cnt[i]) ++k;
		++dp[k - i].x;
		while(lo < n && make_pair(2 * p[lo].x, 2 * p[lo].y) < cnt[i]) ++lo;
		if(lo < n && 2 * p[lo].x == cnt[i].x && 2 * p[lo].y == cnt[i].y) ++dp[k - i].y;
	}
	for(int k = 1; k <= n / 2; ++k) {
		for(int i = 1; i <= k; ++i) {
			ans[i << 1] = (ans[i << 1] + 1ll * dp[k].x * C[k][i]) % mod;
			ans[(i << 1) | 1] = (ans[(i << 1) | 1] + 1ll * dp[k].y * C[k][i]) % mod; 
		}
	}
	for(int i = 1; i < n; ++i) cout << ans[i] << ' ';
	cout << ans[n] << '\n';
	return 0;
}