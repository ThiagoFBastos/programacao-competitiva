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

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	int n;
	cin >> s;
	n = s.size();
	vi p(n + 2), pi(n + 2), minP(n + 2);
	p[0] = pi[0] = 0;
	for(int k = 0; k < n; ++k) {
		p[k + 1] = p[k];
		pi[k + 1] = pi[k];
		if(s[k] == '(') ++p[k + 1], --pi[k + 1];
		else --p[k + 1], ++pi[k + 1];
	}
	minP.back() = 1e9;
	for(int k = n; k; --k) minP[k] = min(minP[k + 1], p[k]);
	int mp = 0;
	bool ok = false;
	for(int k = 0; k <= n; ++k) {
		mp = min(mp, p[k]);
		if(mp >= 0) {
			int mpi = mp;
			for(int j = k + 1; j <= n; ++j) {
				int correcao = p[k] + pi[j] - pi[k] - p[j]; 
				mpi = min(p[k] + pi[j] - pi[k], mpi);
				if(mpi < 0) break;
				else if(correcao + minP[j + 1] >= 0 && p[n] + correcao == 0) {
					ok = true;
					goto fim;
				}
			}
		}
	}
	if(mp >= 0 && p[n] == 0) ok = true;
	fim:
	cout << (ok ? "possible\n": "impossible\n");
	return 0;
}