#include "bits/stdc++.h"

using namespace std;

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

void solve() {
	string s;

	cin >> s;

	vector<int> op(26, -1);
	map<int, int> mp;
	int n = s.size();

	for(int i = 0, p = 0; i < n; ++i) {
		if(s[i] == '(') mp[p++] = i;
		else if(islower(s[i])) {
			int c = s[i] - 'a';
			if(op[c] != -1) {
				cout << "No\n";
				return;
			}
			op[c] = i;
		} else if(s[i] == ')') {
			--p;
			auto it = mp.find(p);
			if(it == mp.end()) continue;
			for(int c = 0; c < 26; ++c) if(op[c] >= it->sc && op[c] <= i) op[c] = -1;
		}
	}

	cout << "Yes\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
