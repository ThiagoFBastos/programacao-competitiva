#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int N = 2e5;
	int n, p[N], f[N];
	priority_queue<int, vector<int> , greater<int>> pq;
	cin >> n;
	memset(f, 0, n * sizeof(int));
	for(int k = 0; k < n - 2; ++k) {
		cin >> p[k];
		++f[--p[k]];
	}
	for(int k = 0; k < n; ++k)
		if(!f[k]) pq.push(k);
	for(int k = 0 ; k < n - 2; ++k) {
		int v = pq.top();
		pq.pop();
		cout << v + 1 << ' ' << p[k] + 1 << '\n';
		if(--f[p[k]] == 0)
			pq.push(p[k]);
	}
	int u, v;
	u = pq.top();
	pq.pop();
	v = pq.top();
	cout << u + 1 << ' ' << v + 1 << '\n';
    return 0;
}
