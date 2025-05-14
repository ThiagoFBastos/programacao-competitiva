#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 1e7 + 10;
 
int values[N], pre[N], suf[N];
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, k;
	int x, a, b, c;
 
	cin >> n >> k;
	cin >> x >> a >> b >> c;
 
	int ans {};
 
	values[0] = x;
 
	for(int i = 1; i < n; ++i)
		values[i] = (1ll * values[i - 1] * a + b) % c;
 
	for(int i = 0; i < n; i += k) {
		pre[i] = values[i];
 
		for(int j = 1; j < k && i + j < n; ++j)
			pre[i + j] = min(values[i + j], pre[i + j - 1]);
 
		int m = min(n - 1, i + k - 1);
 
		suf[m] = values[m];
 
		for(int j = m - 1; j >= i; --j)
			suf[j] = min(values[j], suf[j + 1]);
	}
 
	for(int i = 0; i <= n - k; ++i) {
		if(i % k == 0)
			ans ^= suf[i];
		else
			ans ^= min(suf[i], pre[i + k - 1]);
	}
 
	cout << ans << '\n';
 
	return 0;
}