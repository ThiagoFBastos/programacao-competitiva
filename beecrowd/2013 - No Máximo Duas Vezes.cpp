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

int digitos(ll n) {
	int res = 0;
	while(n > 0) {
		++res;
		n /= 10;
	}
	return res;
}

ll findMax(string& s) {
	int cnt[10] = {0};
	ll ans[21];
	bool menor = false;
	ans[0] = 0;
	for(int i = 0; i < (int)s.size(); ++i) {
		bool ok = false;
		if(menor) {
			for(int j = 9; j >= 0; --j) {
				if(cnt[j] < 2) {
					++cnt[j];
					ans[i + 1] = 10 * ans[i] + j;
					ok = true;
					break;
				}
			}
			if(!ok) return LLONG_MAX;
		} else {
			if(cnt[s[i] - '0'] < 2) {
				ok = true;
				ans[i + 1] = 10 * ans[i] + s[i] - '0';
				++cnt[s[i] - '0'];
			}
			if(ok) continue;	
			for(int k = i; k >= 0; --k) {
				int a1, a2;
				a1 = a2 = -1;
				for(int j = s[k] - '0' - 1; j >= (k == 0); --j) {
					if(cnt[j] < 2) {
						a1 = j;
						break;
					}
				}
				for(int j = k + 1; j < i; ++j) {
					if(k == 0 && s[j] == '0') continue;
					else if(s[j] < s[k]) a2 = max(a2, s[j] - '0');
				}
				if(max(a1, a2) != -1) {
					for(int j = k; j < i; ++j) --cnt[s[j] - '0'];
					++cnt[max(a1, a2)];
					ans[k + 1] = 10 * ans[k] + max(a1, a2);
					i = k;
					ok = true;
					break;
				}
			}
			menor = true;
			if(!ok) return LLONG_MAX;
		}
	}
	return ans[s.size()];
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll n, ans = 0, m = 0;
	int cnt[10] = {0};
	cin >> n;

	int d = digitos(n);

	string s = to_string(n);
	ans = findMax(s);
	if(ans > n) ans = 0;
 
	for(int i = 0; i < d - 1; ++i) {
		for(int j = 9; j >= (i == 0); --j) {
			if(cnt[j] < 2) {
				++cnt[j];
				m = 10 * m + j;
				break;
			}
		}
	}

	cout << max(ans, m) << '\n';

	return 0;
}