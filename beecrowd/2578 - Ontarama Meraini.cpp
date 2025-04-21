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
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

const int maxn = 1e6 + 1;

int cnt_t[maxn][26], cnt_m[26], ag[maxn];
string M, T;

bool ok(int L, int R) {
	for(int i = 0; i < 26; ++i) {
		if(cnt_t[R][i] - cnt_t[L][i] < cnt_m[i])
			return false;
	}
	return true;
}

bool anagrama(int L, int R) {
	for(int i = 0; i < 26; ++i) {
		if(cnt_t[R][i] - cnt_t[L][i] != cnt_m[i])
			return false;
	}
	return true;
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> T >> M;
	
	memset(ag, 0, sizeof(bool) * (1 + T.size()));
	memset(cnt_m, 0, sizeof cnt_m);
	memset(cnt_t[0], 0, sizeof cnt_t[0]);

	for(char ch : M) ++cnt_m[ch - 'a'];
	for(int k = 0; k < (int)T.size(); ++k) {
		for(int i = 0; i < 26; ++i)
			cnt_t[k + 1][i] = cnt_t[k][i];
		++cnt_t[k + 1][T[k] - 'a'];
	}

	ll res = 0;
	int hi = 0;
	
	for(int k = 1; k <= (int)T.size(); ++k) {	
		if(ok(0, k)) {
			for(; hi < k && ok(hi, k); ++hi);
			if(anagrama(hi - 1, k)) 
				ag[k] = 1;
		}
	}

	for(int k = 1; k <= (int)T.size(); ++k)
		ag[k] += ag[k - 1];

	hi = 0;

	for(int k = 1; k <= (int)T.size(); ++k) {
		if(ag[k]) {
			for(; hi < k && ag[k] - ag[hi]; ++hi);
			res += hi - (int)M.size() + 1;
		}
	}

	cout << res << '\n';

	return 0;
}