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

const int maxn = 1 + 1e5;

struct trie_data {
	int t[maxn][26], sz;
	void clear() {
		sz = 1;
		memset(t[0], -1, sizeof t[0]);
	}
	void push(string& s) {
		int k = 0;
		for(int i = 0; i < (int)s.size(); ++i) {
			int nxt = s[i] - 'a';
			if(t[k][nxt] == -1) {
				for(; i < (int)s.size(); ++i) {
					nxt = s[i] - 'a';	
					memset(t[sz], -1, sizeof t[sz]);	
					k = t[k][nxt] = sz++;
				}
				break;
			}
			k = t[k][nxt];
		}
	}
};

ll cnt[26];
int let[26];
trie_data pt, st;

void solve();

void solve() {
	ll ans = 0;
	stack<int> s;
	memset(cnt, 0, sizeof cnt);
	s.push(0);
	while(!s.empty()) {
		auto no = s.top();
		s.pop();
		for(int k = 0; k < 26; ++k) {
			if(st.t[no][k] == -1) continue;
			++cnt[k];
			s.push(st.t[no][k]);
		}
	}
	for(int k = 0; k < 26; ++k) {
		if(pt.t[0][k] != -1)		
			s.push(pt.t[0][k]);
	}
	while(!s.empty()) {
		int no = s.top();
		s.pop();
		for(int k = 0; k < 26; ++k) {
			if(pt.t[no][k] != -1) {
				s.push(pt.t[no][k]);
				ans += let[k];
			} else
				ans += cnt[k];
		}
	}	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(;;) {
		int p, s;
		cin >> p >> s;
		if(!(p or s)) break;
		pt.clear();
		st.clear();
		for(int i = 0; i < p; ++i) {
			string a;
			cin >> a;
			pt.push(a);
		}
		memset(let, 0, sizeof let);
		for(int i = 0; i < s; ++i) {
			string a;
			cin >> a;
			let[a.back() - 'a'] = 1;
			reverse(a.begin(), a.end());
			st.push(a);
		}
		solve();
	}
    return 0;
}