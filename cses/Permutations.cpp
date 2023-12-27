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
	int n;
	cin >> n;
	if(n < 4 && n > 1)
		cout << "NO SOLUTION\n";
	else {
		int *v = new int[n + 1];
		for(int k = 2; k <= n; k += 2)
			v[k] = k / 2;
		for(int k = 1; k <= n; k += 2)
			v[k] = (k + 1) / 2 + n / 2;
		for(int i = 1; i <= n; ++i) cout << v[i] << ' ';
		cout << '\n';
	}
 
	return 0;
} 
