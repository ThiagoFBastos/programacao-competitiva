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

const int maxn = 2e7 + 1;

char s[maxn], inv[10];

int cnt(int n, int k);
int p(int n);

int cnt(int n, int k) {
	int ans = 0;
	while(n >= k) ans += n /= k;
	return ans;
}

int p(int n) {
	if(n <= 0) return 1;
	switch((n - 1) & 3) {
		case 0: return 2;
		case 1: return 4;
		case 2 : return 8;
		default: return 6;
	}
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	for(int i = 1; i <= 9; ++i) {
		for(int k = 1; k <= 9; ++k) {
			if(i * k % 10 == 1) {
				inv[i] = k;
				break;
			}
		}
	}

	s[0] = s[1] = 1;
	
	for(int k = 2; k < maxn; ++k) {
		int n = k;
		while(!(n & 1)) n >>= 1;
		while(n % 5 == 0) n /= 5;
		s[k] = (int)s[k - 1] * n % 10;
	}

	int n, m;

	for(; cin >> n >> m; ) {
		int a, b;
		a = cnt(n, 2) - cnt(n - m, 2);
		b = cnt(n, 5) - cnt(n - m, 5);
		cout << (a < b ? 5 : 1) * p(a - b) * s[n] * inv[(int)s[n - m]] % 10 << '\n';
	}
	return 0;
}