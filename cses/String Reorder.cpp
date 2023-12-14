#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,mmx")
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
int cnt[26], f_max = 0;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	vector<char> l;
	cin >> s;
	memset(cnt, 0, sizeof cnt);
	for(char c : s) ++cnt[c - 'A'];
	for(int i = 0; i < 26; ++i)
		f_max = max(f_max, cnt[i]);
	if(2 * f_max - 1 <= (int)s.size()) {
		int k = 0, i;
		for(i = 0; i < 26; ++i) {
			k = max(k, i + 1);
			while(cnt[i]) {
				--cnt[i];
				while(k < 26 && !cnt[k]) ++k;
				l.push_back(i + 'A');
				if(cnt[i]) {
					if(k == 26) goto finish;
					--cnt[k];
					l.push_back(k + 'A');
				}
			}
		}
		finish:
		if(i < 26) {
			vector<char> x;
			k = (int)l.size() - 1;
			while(k >= 0) {
				if(cnt[i]) {
					if(x.empty()) x.push_back(l[k--]);	
					else if(x.back() != i + 'A' && l[k] != i + 'A') {
						x.push_back(i + 'A');
						--cnt[i];
					} else x.push_back(l[k--]);
				} else x.push_back(l[k--]);
			}
			if(cnt[i]) x.push_back(i + 'A');
			reverse(x.begin(), x.end());
			k = 0;
			while(k < (int)x.size() && x[k] != i + 'A') ++k;
			memset(cnt, 0, sizeof cnt);
			for(int j = k + 1; j < (int)x.size(); ++j) 
				if(x[j] != i + 'A') 
					++cnt[x[j] - 'A'];
			i = 0;
			for(int j = k + 1; j < (int)x.size(); j += 2) {
				while(i < 26 && !cnt[i]) ++i;
				x[j] = i + 'A';
				--cnt[i];
			}
			cout << string(x.begin(), x.end()) << '\n';
		} else
			cout << string(l.begin(), l.end()) << '\n';
	} else
		cout << "-1\n";
	return 0;
}
