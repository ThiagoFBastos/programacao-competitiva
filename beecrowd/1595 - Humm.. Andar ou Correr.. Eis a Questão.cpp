#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
const int MAXN = 1e5;
int main() {
	ios_base :: sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	int t, v[MAXN];
	cin >> t;
	while(t--) {
		int s, c, r;
		ld tim = 0;
		cin >> s >> c >> r;
		for(int i = 0; i < s; ++i) cin >> v[i];
		sort(v, v + s);
		for(int k = 0; k < c; ++k) tim += 1.0L / (v[k] + r);
		for(int k = c; k < s; ++k) tim += 1.0L / v[k];
		cout << fixed << setprecision(2) << tim << '\n';
	}
	return 0;
}