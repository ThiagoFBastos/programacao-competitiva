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
	string s, t;

	cin >> s >> t;

	vector<vector<int>> p(26);
	
	for(int i = 0; i < (int)s.size(); ++i) p[s[i] - 'a'].push_back(i);

	int cur = 0, cycle = 0;

	for(int i = 0; i < (int)t.size(); ++i) {
		int ch = t[i] - 'a';
		if(p[ch].empty()) {
			cout << "-1\n";
			return;
		} else if(p[ch].back() < cur) {
			++cycle;
			cur = 0;
		}
		int k = *lower_bound(p[ch].begin(), p[ch].end(), cur);
		cur = k + 1;
	}

	cout << (i64)s.size() * cycle + cur << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
