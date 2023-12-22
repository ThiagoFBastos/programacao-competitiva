#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

using namespace std;

template<class T>
using ordered_set = tree<T ,  null_type , less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;


#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

int n, q;
ordered_set<int> S[26];
ordered_set<pair<char, int>> P;
string s;

int count(int c, int l, int r) {
	auto& st = S[c];
	return (int)st.order_of_key(r + 1) - (int)st.order_of_key(l);
}

void upd(int k, char c) {
	S[s[k]-'a'].erase(k);
	P.erase(make_pair(s[k], k));
	S[c-'a'].insert(k);
	P.insert(make_pair(c, k));
	s[k] = c;
}

void solve() {
	cin >> n >> s >> q;

	for(int i = 0; i < n; ++i) {
		S[s[i] - 'a'].insert(i);
		P.insert(make_pair(s[i],i));
	}

	for(int i = 0; i < 26; ++i) S[i].insert(n);

	while(q--) {
		int t, a, b;
		char c;
		cin >> t >> a;
		--a;
		if(t == 1) {
			cin >> c;
			upd(a, c);
		} else {
			int pos = 0, cur = a;
			bool check = true;

			cin >> b;

			--b;

			pos = *S[s[a]-'a'].find_by_order(count(s[a] - 'a', 0, n - 1) - count(s[a]-'a', a, b));
			pos = P.order_of_key(make_pair(s[a], pos));

			for(int i = 0; i < 26 && check; ++i) {
				int l = count(i, a, b);
				if(!l) continue;
				check = check && pos + l <= n &&P.find_by_order(pos+l-1)->fi == i + 'a';
				check = check && P.find_by_order(pos)->fi == i + 'a';
				check = check && count(i, cur, cur + l - 1) == l;
				pos += l;
				cur += l;
			}

			cout << (check ? "Yes\n" : "No\n");
		}
	}	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

