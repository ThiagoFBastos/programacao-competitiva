#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>; 

void solve() {
	
	int n, q;
	string s;

	cin >> n >> s >> q;

	vector<set<int>> S(26);

	for(int i = 0; i < n; ++i) S[s[i] - 'a'].insert(i);
	for(int i = 0; i < 26; ++i) S[i].insert(n);

	while(q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int k;
			char ch;
			cin >> k >> ch;
			--k;
			S[s[k] - 'a'].erase(k);
			S[ch - 'a'].insert(k);
			s[k] = ch;
		} else {
			int l, r, cnt = 0;
			cin >> l >> r;
			--l, --r;
			for(int i = 0; i < 26; ++i)
				cnt += *S[i].lower_bound(l) <= r;
			cout << cnt << '\n';
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
