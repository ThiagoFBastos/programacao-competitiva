#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5;
int n, q, prox[18][MAXN], dp[MAXN], p[19], LOG;
pair<int, int> movies[MAXN];
int films(int first, int& last, int endtime) {
	int res = 1;
	for(int i = LOG; i >= 0; --i) {
		int nxt = prox[i][first];
		if(movies[nxt].second <= endtime) {
			res += p[i];
			first = nxt;
		}
	}
	last = first;
	return res;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	cout.tie(0);
	p[0] = 1;
	for(int i = 1; i <= 18; ++i) p[i] = p[i - 1] << 1;
	cin >> n >> q;
	for(int i = 0; i < n; ++i) cin >> movies[i].first >> movies[i].second;
	sort(movies, movies + n);	
	for(int i = n - 1; i >= 0; --i) {
		dp[i] = i;
		if(i < n - 1 && movies[dp[i + 1]].second < movies[i].second) dp[i] = dp[i + 1];
		int k = lower_bound(movies, movies + n, make_pair(movies[i].second, 0)) - movies;
		if(k == n) prox[0][i] = i;
		else prox[0][i] = dp[k];
	}
	LOG = 31 - __builtin_clz(n);
	for(int i = 1; i <= LOG; ++i)
		for(int k = 0; k < n; ++k)
			prox[i][k] = prox[i - 1][prox[i - 1][k]];
	while(q--) {
		int a, b;
		cin >> a >> b;
		int k = lower_bound(movies, movies + n, make_pair(a, 0)) - movies;
		if(k == n)
			cout << "0\n";
		else {
			k = dp[k];				
			if(movies[k].second <= b) {
				int R, res;
				films(k, R, b);
				if(k == R) cout << "1\n";
				else cout << 1 + films(k, R, movies[R].first) << '\n';
			}
			else cout << "0\n";
		}
	}
	return 0;
}
