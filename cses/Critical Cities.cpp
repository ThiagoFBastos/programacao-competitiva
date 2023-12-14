#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	queue<int> S;
	const int MAXN = 1e5;
	vii G[MAXN];
	int n, m, lv[MAXN], p[MAXN][2], cnt[MAXN + 1];
	bool used[2 * MAXN];
	cin >> n >> m;
	for(int i = 0; i < n; ++i) {
		cnt[i] = 0;
		p[i][0] = p[i][1] = lv[i] = -1;
	}
	for(int i = 0; i < m; ++i) {
		int u, v;
		used[i] = false;
		cin >> u >> v;
		--u, --v;
		G[u].push_back({v, i});
	}
	S.push(0);
	p[0][0] = 0;
	p[0][1] = -1;
	while(!S.empty()) {
		int v = S.front();
		S.pop();
		if(v == n - 1) break;
		for(auto [u, k] : G[v]) {
			if(p[u][0] == -1) {
				p[u][0] = v;
				p[u][1] = k;
				S.push(u);
			}
		}
	}
	vector<int> path;
	for(int v = n - 1; v; v = p[v][0]) {
		used[p[v][1]] = true;
		path.push_back(v);
	}
	path.push_back(0);
	reverse(path.begin(), path.end());
	for(int k = 0; k < path.size(); ++k)
		lv[path[k]] = k;
	for(int v : path) {
		queue<int> Q;
		Q.push(v);
		while(!Q.empty()) {
			int u = Q.front();
			Q.pop();
			while(!G[u].empty()) {
				auto [w, k] = G[u].back();
				G[u].pop_back();
				if(!used[k]) {
					used[k] = true;
					if(lv[w] == -1) 
						Q.push(w);
					else if(lv[v] + 1 < lv[w]) {
						++cnt[1 + lv[v]];
						--cnt[lv[w]];
					}
				}
			}		
		}
	}
	for(int i = 1; i < path.size(); ++i) cnt[i] += cnt[i - 1];
	vector<int> C;
	for(int i = 0; i < path.size(); ++i) if(cnt[i] == 0) C.push_back(path[i]);
	sort(C.begin(), C.end());
	cout << C.size() << '\n';
	for(int v : C) cout << v + 1 << ' ';
	cout << '\n';
	return 0;
}
