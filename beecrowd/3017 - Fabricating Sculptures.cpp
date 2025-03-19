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

const int mod = 1e9 + 7, maxn = 5002;

int p1[maxn][maxn], p2[maxn][maxn], S, B;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> S >> B;

	p1[B - S][0] += S;
	p2[B - S][0]++;

	for(int f = B - S; f; --f) {

		int lim = min(f, S);

		for(int k = 1; k <= lim; ++k) {

			int x, dp;

			p1[f][k] += p1[f][k - 1];
			p2[f][k] += p2[f][k - 1];

			if(p1[f][k] >= mod) p1[f][k] -= mod;
			if(p2[f][k] >= mod) p2[f][k] -= mod;

			dp = (mod + (p1[f][k] - (k - 1LL) * p2[f][k]) % mod) % mod;
			x = 1LL * k * dp % mod;
			
			p1[f - k][0] += x;
			p1[f - k][k + 1] -= x;
			p2[f - k][0] += dp;
			p2[f - k][k + 1] -= dp; 

			if(p1[f - k][0] >= mod) p1[f - k][0] -= mod;
			if(p1[f - k][k + 1] < 0) p1[f - k][k + 1] += mod;
			if(p2[f - k][0] >= mod) p2[f - k][0] -= mod;
			if(p2[f - k][k + 1] < 0) p2[f - k][k + 1] += mod;
		}
	}
	cout << p2[0][0] << '\n';
	return 0;
}