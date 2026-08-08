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
	string s, p;
	vii cnt(26, make_pair(0, 0));
	cin >> s;
	for(char c : s) ++cnt[c - 'a'].first;
	if(max_element(cnt.begin(), cnt.end())->first == (int)s.size()) cout << "-1\n";
	else {	
		for(int k = 0; k < 26; ++k) cnt[k].second = k;
		sort(cnt.rbegin(), cnt.rend());
		for(int k = 0; k < 26; ++k) {
			if(!cnt[k].first) continue;
			p += string(min(cnt[k].first, (int)s.size() / 2), cnt[k].second + 'a');
			cnt[k].first -= min(cnt[k].first, (int)s.size() / 2);
		}
		for(int k = 25; k >= 0; --k) if(cnt[k].first) p += string(cnt[k].first, cnt[k].second + 'a');
		cout << p << '\n';
	}
	return 0;
}