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

double dp[1 << 15];
bool marked[1 << 15];

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, s;
	double P[15];

	cin >> n >> m;
	s = 1 << n;

	dp[s - 1] = 1;

	fill(P, P + n, 0);

	for(int k = 0; k < m; ++k) {
		int a, b;
		double p;
		cin >> a >> b >> p;
		--a, --b;
		a = (1 << a) | (1 << b);
		for(int mask = 0; mask < s; ++mask) {
			if((mask & a) == a) {
				dp[mask ^ 1 << b] += dp[mask] * p;
				dp[mask] *= (1 - p);
			}
		}
	}
	cout.precision(8);
	cout.setf(ios_base :: fixed);
	for(int mask = 0; mask < s; ++mask) {
		for(int k = 0; k < n; ++k) {
			if(mask & 1 << k)
				P[k] += dp[mask];
		}
	}
	for(int k = 0; k < n; ++k) cout << P[k] << '\n';
	return 0;
}

