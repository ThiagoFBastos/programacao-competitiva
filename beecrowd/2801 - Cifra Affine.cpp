#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
int euclides(int a, int b, int& x, int& y) {
	if(b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int z, w, g;
	g = euclides(b, a % b, z, w);
	y = z - 1LL * a / b * w;
	x = w;
	return g;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int N = 1e5;
	int n, a, x, y, b, t, msg[N];
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> msg[i];
	cin >> t >> a >> b;
	if(euclides(a, t, x, y) == 1) {
		for(int k = 0; k < n - 1; ++k) cout << (1LL * x * (msg[k] - b) % t + t) % t << ' ';
		cout << (1LL * x * (msg[n - 1] - b) % t + t) % t << '\n';
	}
	else 
		cout << "DECIFRAGEM AMBIGUA\n";
	return 0;
}