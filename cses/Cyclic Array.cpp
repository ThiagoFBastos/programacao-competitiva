#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 2e5;
	int n, r[1 + MAXN], high, last[1 + MAXN];
	long long k, p[MAXN + 1];
	cin >> n >> k;
	p[0] = 0;
	for(int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		p[i] = x + p[i - 1];
		r[i] = last[i] = 0;
	}
	high = n;
	for(int i = n; i; --i) {
		while(high && p[high] > p[i - 1] + k) --high;
		++high;
		if(high == n + 1) {
			r[i] = 1;
			last[i] = i;
		}
		else {
			last[i] = last[high];
			r[i] = 1 + r[high];
		}
		--high;
	}
	int min_k = r[1];
	for(int i = 2; i <= n; ++i) if(p[i - 1] + p[n] - p[last[i] - 1] <= k) min_k = min(min_k, r[i]);
	cout << min_k << '\n';
	return 0;
}
