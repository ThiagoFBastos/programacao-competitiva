#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

const int N = 1e6 + 10, K = 20;

int fac[N], d[N], cycle[N], in[N], sp[K][N], n, k;
i64 sum[K][N];

void sieve(int n) {
	d[1] = 1;
	for(int i = 2; i <= n; ++i) {
		if(!fac[i]) for(int k = i; k <= n; k += i) fac[k] = i;
		int k = i, p = fac[i], j = 1;
		while(fac[k] == p) ++j, k /= p;
		d[i] = j * d[k];
	}
}

int prv(int i) {
	int j = i + d[i];
	if(j >= n) j -= n;
	return j;
}

int get(int i) {
	if(cycle[i] != -1) return cycle[i];
	int j = prv(i);
	return cycle[i] = 1 + get(j);
}

void solve() {

	queue<int> q;

	cin >> n >> k;

	if(k > n) {
		cout << "-1\n";
		return;
	}
	
	sieve(n);
	memset(cycle, -1, sizeof(int) * n);

	for(int i = 1; i < n; ++i) ++in[prv(i)];
	for(int i = 0; i < n; ++i) if(!in[i]) q.push(i);

	while(!q.empty()) {
		int i = q.front(); q.pop();
		int j = prv(i);
		if(--in[j] == 0) q.push(j);
	}

	cycle[0] = 1;

	for(int i = 1; i < n; ++i) {
		if(in[i] < 1 || cycle[i] != -1) continue;
		vector<int> c;
		for(int j = i; cycle[j] < 0; j = prv(j)) {
			c.pb(j);
			cycle[j] = 0;
		}
		for(int u : c) cycle[u] = c.size();
	}

	for(int i = 0; i < n; ++i) {
		cycle[i] = get(i);
		sp[0][i] = prv(i);
		sum[0][i] = i;
	}

	int lg = 32 - __builtin_clz(n), who = -1;
	i64 bests = INFLL;

	for(int i = 1; i < lg; ++i) {
		for(int j = 0; j < n; ++j) {
			sp[i][j] = sp[i - 1][sp[i - 1][j]];
			sum[i][j] = sum[i - 1][j] + sum[i - 1][sp[i - 1][j]];
		}
	}

	for(int i = 0; i < n; ++i) {
		if(cycle[i] < k) continue;
		i64 s = 0;
		int cur = i;
		for(int j = 0; j < lg; ++j) {
			if((k >> j) & 1) {
				s += sum[j][cur];
				cur = sp[j][cur];
			}
		}
		if(bests > s) bests = s, who = i;
	}
	
	if(who < 0) {
		cout << "-1\n";
		return;
	}

	for(int i = 0; i < k; ++i) {
		cout << who << ' ';
		who = prv(who);
	}
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
