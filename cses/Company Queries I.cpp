#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
#define MAXN 200000
vi G[MAXN];
int h[MAXN], pa[MAXN];
void dfs(int v, int hg = 0) {
	h[v] = hg;
	for(int u : G[v]) {
		if(h[u] == -1) {
			pa[u] = v;
			dfs(u, hg + 1);	
		}
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int **st, n, q, LOG[MAXN + 1];
	cin >> n >> q;
	LOG[1] = 0;
	for(int i = 2; i <= n; ++i)
		LOG[i] = 1 + LOG[i >> 1];
	memset(h, -1, n * sizeof(int));
	for(int i = 1; i < n; ++i) {
		int boss;
		cin >> boss;
		G[boss - 1].push_back(i);
	}
	pa[0] = 0;
	dfs(0);
	st = new int*[n];
	int N = LOG[n];
	for(int i = 0; i < n; ++i) {
		st[i] = new int[N + 1];
		st[i][0] = pa[i];
	}
	for(int i = 1; i <= N; ++i)
		for(int j = 0; j < n; ++j)
			st[j][i] = st[st[j][i - 1]][i - 1];
	while(q--) {
		int x, k;
		cin >> x >> k;
		--x;
		if(h[x] < k)
			cout << -1 << '\n';
		else {
			for(int i = N; i >= 0; --i) {
				if(k >= (1 << i)) {
					k -= 1 << i;
					x = st[x][i];
				}
			}
			cout << x + 1 << '\n';
		}
	}
    return 0;
}
 
