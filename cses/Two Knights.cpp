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
#define sq(n) 1LL * n * n
ll count(int n) {
	return sq(n) * (sq(n) - 1) / 2 - 4LL * (n - 2LL) * (n - 1LL);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for(int k = 1; k <= n; ++k) cout << count(k) << '\n';
	return 0;
} 
