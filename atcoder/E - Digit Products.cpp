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

i64 K[19];

string s;

map<ii, i64> S;

i64 count(int n, int k, bool l) {
	if(n == 0) return k == 0;
	if(l && S.count(make_pair(n, k))) return S[{n, k}];

	i64 ans = 0;

	if(l) {
		if(!k) return S[{n, k}] = K[n];
		for(int d = 1; d <= 9; ++d) ans += count(n - 1, k / d, true);
		S[{n, k}] = ans;
	} else {
		for(int d = 1; d < s[n - 1] - '0'; ++d) ans += count(n - 1, k / d, true);
		if(s[n - 1] != '0') ans += count(n - 1, k / (s[n - 1] - '0'), false);
	}

	return ans;
}

void solve() {
	i64 n;
	int k;

	K[0] = 1;
	for(int i = 1; i <= 18; ++i) K[i] = 9 * K[i - 1]; 

	cin >> n >> k;

	s = to_string(n);
	reverse(s.begin(), s.end());

	for(int i = 1; i < (int)s.size(); ++i) n -= count(i, k, true);
	
	n -= count((int)s.size(), k, false);
	
	cout << n << '\n';
}


int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

