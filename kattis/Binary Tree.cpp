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
const int mod = 21092013;
vi p[127];
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	for(int tt = 1; tt <= t; ++tt) {
		string s, t;
		int L = 0, R = 0, ans, lou = 0, lor = 0, lol = 0, u;
		stack<char> S;
		cin >> s >> t;
		for(char c : s) {
			if(c == 'U') {
				if(!S.empty()) 
					S.pop();
			}
			else S.push(c);
		}
		for(int k = 0; k < (int)t.size(); ++k) p[t[k]].push_back(k);
		s = "";
		while(!S.empty()) {
			s += S.top();
			S.pop();
		}
		reverse(s.begin(), s.end());
		vi cnt(t.size() + 1);
		cnt.back() = 1;
		for(int k = (int)t.size() - 1; k >= 0; --k) {
			int z;
			cnt[k] = cnt[k + 1];
			if(t[k] == 'U') continue;
			else if(t[k] == 'L') {
				z = cnt[k] - L;
				L += z;
				if(L >= mod) L -= mod;
				if(L < 0) L += mod;
			} else {
				z = cnt[k] - R;
				R += z;
				if(R >= mod) R -= mod;
				if(R < 0) R += mod;
			}
			cnt[k] += z;
			if(cnt[k] >= mod) cnt[k] -= mod;
			if(cnt[k] < 0) cnt[k] += mod;
		}
		ans = cnt[0];
		u = min(p['U'].size(), s.size());
		for(int k = (int)s.size() - 1; k >= (int)s.size() - u; --k) {
			while(lol < (int)p['L'].size() && p['L'][lol] < p['U'][lou]) ++lol;
			while(lor < (int)p['R'].size() && p['R'][lor] < p['U'][lou]) ++lor;
			if(s[k] == 'L' && lor < (int)p['R'].size()) ans += cnt[p['R'][lor] + 1];
			else if(s[k] == 'R' && lol < (int)p['L'].size()) ans += cnt[p['L'][lol] + 1];
			++ans;
			if(ans >= mod) ans -= mod;
			++lou;
		}
		cout << "Case " << tt << ": " << ans << '\n';
		for(char c : {'L', 'R', 'U'}) p[c].clear();
	}
	return 0;
}