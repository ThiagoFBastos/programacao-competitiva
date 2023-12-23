#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	
	string s;

	cin >> s;

	int n = s.size();

	s += "#";

	for(int i = 0; i < n; ++i) {
		if(s[i] == s[i + 1]) {
			cout<<i+1<<' '<<i+2<<'\n';
			return;
		} else if(s[i] == s[i + 2]) {
			cout<<i+1<<' '<<i+3<<'\n';
			return;
		}
	}

	cout<<"-1 -1\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
