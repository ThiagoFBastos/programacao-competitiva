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
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int a, b;
		cin >> a >> b;
		int y = 2 * b - a;
		if(y >= 0 && y % 3 == 0 && b - 2LL * y / 3 >= 0) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
} 
