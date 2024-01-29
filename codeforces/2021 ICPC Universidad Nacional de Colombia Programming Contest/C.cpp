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
	string s;
	cin >> s;
	if(cin.eof()) exit(0);
	int n = s.size();
	i64 ans = 0;
	vector<int> pre(n);
	for(int i = 0; i < n; ++i) {
		pre[i] = 0;
		for(int j = i + 1; j < n; ++j) {
			int k = pre[j - 1];
			while(k > 0 && s[j] != s[k + i]) k = pre[i + k - 1];
			pre[j] = k;
			if(s[j] == s[k + i]) ++pre[j];
			ans += pre[j];
		}
	}
	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
 	return 0;
}

