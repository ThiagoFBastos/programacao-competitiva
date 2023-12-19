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
vi T[MAXN];
int c[MAXN], in[MAXN], tour[MAXN], last[MAXN], t_in = 0, n;
void dfs(int v) {
	tour[t_in] = last[v] = v;
	in[v] = t_in++;
	for(int u : T[v]) {
		if(in[u] == -1) {
			dfs(u);
			last[v] = last[u];
		}
	}
}
int ft[MAXN + 1];
void update(int k) {
	while(k <= n) {
		++ft[k];
		k += k & -k;
	}
}
int query(int r) {
	int ans = 0;
	while(r > 0) {
		ans += ft[r];
		r -= r & -r;
	}
	return ans;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; ++i) {
		cin >> c[i];
		in[i] = -1;
	}
	vi colors(c, c + n);
	list<int> pos[MAXN];
	sort(colors.begin(), colors.end());
	unique(colors.begin(), colors.end());
	for(int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		T[u].push_back(v);
		T[v].push_back(u);
	}
	dfs(0);
	memset(ft, 0, (n + 1) * sizeof(int));
	for(int i = 0; i < n; ++i) {
		int v = tour[i];
		c[v] = lower_bound(colors.begin(), colors.end(), c[v]) - colors.begin();
		if(pos[c[v]].empty())
			update(i + 1);
		pos[c[v]].push_back(i);
	}
	int ans[MAXN];
	for(int i = 0; i < n; ++i) {
		int v = tour[i];
		int r = in[last[v]];
		ans[v] = query(r + 1) - query(in[v]);
		pos[c[v]].pop_front();
		if(!pos[c[v]].empty())
			update(pos[c[v]].front() + 1);
	}
	for(int i = 0; i < n; ++i) cout << ans[i] << ' ';
	cout << '\n';
    return 0;
}
