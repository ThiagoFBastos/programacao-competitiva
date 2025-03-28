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
const int maxn = 1e5 + 101;
int dp[maxn], a[1000];
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
static void read(int&);
void read(int& n) {
	register int ch = getchar_unlocked();
	while(ch < '0') ch = getchar_unlocked();
	n ^= n;
	while(ch >= '0') {
		n = (n << 3) + (n << 1) + ch - '0';
		ch = getchar_unlocked();
	}
}
int main() {
	while(true) {
		int n, soma = 0, s = 0;
		read(n);
		if(n == 0) break;
		for(int i = 0; i < n; ++i) {
			read(a[i]);
			s += a[i];
		}
		for(int i = 0; i <= s; ++i)
			dp[i] = INT_MIN;
		dp[0] = dp[s] = 0;
		for(register int i = 0; i < n; ++i) {
			int x = a[i];
			for(register int k = soma; k >= 0; --k) {
				dp[k + x] = MAX(dp[k + x], dp[k]);
				dp[k + (x << 1)] = MAX(dp[k + (x << 1)], dp[k] + x);
			}
			soma = MIN(soma + (x << 1), s);
		}
		printf("%d\n", dp[soma]);
	}
	return 0;
}