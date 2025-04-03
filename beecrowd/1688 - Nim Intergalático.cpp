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

int cnt[64];

ll xor_range(ll);
ll xor_range(ll, ll);

ll xor_range(ll a) {
	if(a <= 0) return 0;
	memset(cnt, 0, sizeof cnt);
	int k = 0;
	ll na = 1, ans = 0;
	for(; a > 0; a >>= 1) {
		int last = a & 1;
		cnt[k] ^= na & last;
		if(k == 1) cnt[0] ^= last;
		na += (ll)last << k; 
		++k;
	}
	for(int i = 0; i < k; ++i) ans |= (ll)cnt[i] << i;
	return ans;
}

ll xor_range(ll a, ll b) {
	return xor_range(b) ^ xor_range(a - 1);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n;
	int q;
	while(cin >> n >> q) {
		ll o = xor_range(1, n);
		while(q--) {
			ll a, b, k;
			cin >> a >> b >> k;
			cout << (o ^ xor_range(a, b) ^ xor_range(a + k, b + k) ? "JABBA" : "HAN") << '\n';
		}
	}
  	return 0;
}