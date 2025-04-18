#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
typedef long long ll;
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, i;
		long double p;
		cin >> n >> p >> i;
		if(fabs(p) < 1e-9) cout << "0.0000\n";
		else cout << fixed << setprecision(4) << p * pow(1.0L - p, i - 1) / (1.0L - pow(1.0L - p, n)) << '\n';
	}
	return 0;
}