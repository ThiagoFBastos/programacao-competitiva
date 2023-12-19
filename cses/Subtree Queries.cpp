#pragma optimize("O3")
#pragma target("sse,sse2")
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
int v[MAXN], tour[2 * MAXN], p[MAXN], last[MAXN], k = 0, n;
ll ft[2 * MAXN + 1];
vi T[MAXN];
void dfs(int w) {
	last[w] = w;
	for(int u : T[w]) {
		if(last[u] == -1) {
			if(p[w] == -1) {p[w] = k; tour[k++] = v[w];}
			dfs(u);
			last[w] = last[u];
		}
	}
	if(last[w] == w) {
		p[w] = k;
		tour[k++] = v[w];
	}
}
void update(int i, int v) {
	while(i <= k) {
		ft[i] += v;
		i += i & -i;
	}
}
ll query(int r) {
	ll ans {};
	while(r > 0) {
		ans += ft[r];
		r -= r & -r;
	}
	return ans;
}
ll query(int l, int r) {
	return query(r) - query(l - 1);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int q;
	cin >> n >> q;
	for(int i = 0; i < n; ++i) {
		cin >> v[i];
		last[i] = p[i] = -1;
	}
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		T[u].push_back(v);
		T[v].push_back(u);
	}
	dfs(0);
	memset(ft, 0, (k + 1) * sizeof(ll));
	for(int i = 0; i < k; ++i)
		update(i + 1, tour[i]);
	while(q--) {
		int t, a;
		cin >> t >> a;
		--a;
		if(t == 1) {
			int b;
			cin >> b;
			update(p[a] + 1, b - v[a]);
			v[a] = b;
		}
		else
			cout << query(p[a] + 1, p[last[a]] + 1) << '\n';
	}
    return 0;
}
