#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2,sse3,sse4,avx,avx2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MOD 1000000007
int expmod(int n, int p) {
	if(p == 0) return 1;
	int r = expmod(n, p >> 1);
	r = 1LL * r * r % MOD;
	return p & 1 ? 1LL * r * n % MOD : r;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	cout << expmod(2, n) << '\n';
	return 0;
} 
