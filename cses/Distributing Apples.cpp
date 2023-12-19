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
	int n, m;
	cin >> n >> m;
	int N = n + m - 1;
	int *fm = new int[N + 1];
	fm[0] = 1;
	for(int i = 1; i <= N; ++i) fm[i] = 1LL * fm[i - 1] * i % MOD;
	cout << 1LL * fm[N] * expmod(1LL * fm[N - m] * fm[m] % MOD, MOD - 2) % MOD << '\n';
	return 0;
}
