#include "bits/stdc++.h"
using namespace std;
int X[20], V[20], pai[1 << 20];
void solve() {
	int n, c, x, v;
	auto ans = make_pair(0LL, 0);
	queue<int> q;
	cin >> n >> c >> x >> v;
	memset(pai, -1, sizeof(int) << n);
	pai[0] = 0;
	for(int i = 0; i < n; ++i) {
		cin >> X[i] >> V[i];
		if(X[i] + x >= 0 && V[i] + v >= 0) {
			pai[1 << i] = 0;
			q.push(1 << i);
		}
	}
	while(!q.empty()) {
		int S = q.front();
		long long _X = x, _V = v;
		q.pop();
		for(int j = S; j; j -= j & -j) {
			int k = __builtin_ctz(j);
			_X += X[k];
			_V += V[k];
		}
		for(int j = ~S & ((1 << n) - 1); j; j -= j & -j) {
			int k = __builtin_ctz(j);
			if(pai[S ^ 1 << k] == -1 && _X + X[k] >= 0 && _V + V[k] >= 0) {
				pai[S ^ 1 << k] = S;
				q.push(S ^ 1 << k);
			}
		}
	}
	for(int w = 0; w < (1 << n); ++w) {
		if(pai[w] != -1) {
			long long _X = x, _V = v;
			for(int j = w; j; j -= j & -j) {
				int k = __builtin_ctz(j);
				_X += X[k];
				_V += V[k];
			}
			ans = max(ans, make_pair(_X * c + _V, w));
		}
	}
	cout << __builtin_popcount(ans.second) << '\n';
	stack<int> S;
	for(int v = ans.second; v; v = pai[v]) S.push(1 + __builtin_ctz(v ^ pai[v]));
	for(; S.size() > 1; S.pop()) cout << S.top() << ' ';
	if(!S.empty()) cout << S.top();
	cout << '\n';
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}