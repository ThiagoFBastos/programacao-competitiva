#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, k;
	int x, a, b, c;
 
	cin >> n >> k;
	cin >> x >> a >> b >> c;
 
	vector<long long> v(n);
	long long ans = 0;
 
	v[0] = 0;
	v[1] = x;
 
	for(int i = 2; i <= n; ++i)
		v[i] = (v[i - 1] * a + b) % c;
 
	for(int i = 1; i <= n; ++i)
		v[i] ^= v[i - 1];
 
	for(int i = k; i <= n; ++i)
		ans ^= v[i] ^ v[i - k];
	
	cout << ans << '\n';
 
	return 0;
}