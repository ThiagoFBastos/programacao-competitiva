#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
#define MOD1 1000000007
#define MOD2 1000000009
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	int n = s.size();
	vector<int> h1(n + 1), h2(n + 1), pw1(n + 1), pw2(n + 1);
	h1[0] = h2[0] = 0;
	pw1[0] = pw2[0] = 1;
	for(int i = 0; i < n; ++i) {
		pw1[i + 1] = 26LL * pw1[i] % MOD1;
		pw2[i + 1] = 26LL * pw2[i] % MOD2;
		h1[i + 1] = (h1[i] + 1LL * pw1[i + 1] * (s[i] - 'a')) % MOD1;
		h2[i + 1] = (h2[i] + 1LL * pw2[i + 1] * (s[i] - 'a')) % MOD2;
	}
	vector<int> ans;
	for(int k = 0; k < n; ++k) {
		int a = 1LL * pw1[n - 1] * h1[k + 1] % MOD1;
		int b = 1LL * pw1[k] * (h1[n] - h1[n - k - 1]) % MOD1;
		int c =  1LL * pw2[n - 1] * h2[k + 1] % MOD2;
		int d =	1LL * pw2[k] * (h2[n] - h2[n - k - 1]) % MOD2;
		b = (b + MOD1) % MOD1;	
		d = (d + MOD2) % MOD2;
		if(a == b && c == d) ans.push_back(k + 1);
	}
	if(ans.back() == n) ans.pop_back();
	for(int p : ans) cout << p << ' ';
	cout << '\n';
	return 0;
}
