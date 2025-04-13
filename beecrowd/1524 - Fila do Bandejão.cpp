#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
const int N = 1000;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k, dist[N], a[N];
	dist[0] = 0;
	while(cin >> n >> k) {
		int soma = 0;
		a[0] = 0;
		for(int i = 1; i < n; ++i) {
			cin >> dist[i];
			a[i] = dist[i] - dist[i - 1];
		}
		sort(a, a + n, greater<int>());
		for(int i = 0; i < k - 1; ++i) soma += a[i];
		cout << dist[n - 1] - soma << '\n';
	}
	return 0;
}