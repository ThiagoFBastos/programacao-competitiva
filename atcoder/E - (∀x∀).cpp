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

const int mod = 998244353;

void solve() {
	string s;
	int n;

	cin >> n >> s;
	
	int mid = (n + 1) / 2;
	i64 ans = 0;

	vector<i64> pt(n + 1);
	pt[0] = 1;

	for(int i = 1; i <= n; ++i) pt[i] = (i64)pt[i - 1] * 26 % mod;

	for(int i = 0; i < mid; ++i) {
		int ch = s[i] - 'A';
		ans = (ans + (i64)pt[mid - i - 1] * ch) % mod; 	
	}

	string X = s.substr(0, mid);
	string p = X;
	if(n & 1) X.pop_back();
	reverse(X.begin(), X.end());
	p += X;
	cout << (ans + (p <= s)) % mod << '\n';	
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}
