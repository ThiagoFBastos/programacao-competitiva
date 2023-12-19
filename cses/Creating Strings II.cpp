#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MOD 1000000007
int expmod(int a, int p) {
	if(p == 0) return 1;
	int r = expmod(a, p >> 1);
	r = 1LL * r * r % MOD;
	return p & 1 ? 1LL * r * a % MOD : r;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;
	int n = s.size();
	int count[26] = {0};
	int *fm = new int[n + 1];
	fm[0] = 1;
	for(int i = 1; i <= n; ++i) fm[i] = 1LL * fm[i - 1] * i % MOD;
	for(char c : s) ++count[c - 'a'];
	int x = 1;
	for(int k = 0; k < 26; ++k) x = 1LL * x * fm[count[k]] % MOD;
	cout << 1LL * fm[n] * expmod(x, MOD - 2) % MOD << '\n';
	return 0;
}
