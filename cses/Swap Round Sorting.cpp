#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
const int MAXN = 2e5;
int n, x[MAXN], vis[MAXN], nxt[MAXN];
void dfs(vi& cycle, int v) {
	vis[v] = 1;
	cycle.push_back(v);
	if(!vis[nxt[v]]) dfs(cycle, nxt[v]);
}
vii round() {
	for(int i = 0; i < n; ++i) {
		nxt[i] = x[i];
		vis[i] = 0;
	}
	vii p;
	for(int i = 0; i < n; ++i) {
		if(!vis[i] && nxt[i] != i) {
			vi cycle;
			dfs(cycle, i);
			if(cycle.size() == 2)
				p.push_back({cycle[0], cycle[1]});
			else {
				for(int k = 0; k < cycle.size() / 2; ++k)
					p.push_back({cycle[k], cycle[(int)cycle.size() - k - 1]});
			}
		}
	}
	for(auto [a, b] : p)
		swap(x[a], x[b]);
	return p;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; ++i) {
		cin >> x[i];
		--x[i];
	}
	vector<vii> rounds;
	for(int k = 0; k < 2; ++k) {
		vii r = round();
		if(r.empty()) break;
		rounds.push_back(r);
	}
	cout << rounds.size() << '\n';
	for(vii& r : rounds) {
		cout << r.size() << '\n';
		for(auto [a, b] : r)
			cout << a + 1 << ' ' << b + 1 << '\n';
	}
	return 0;
}
